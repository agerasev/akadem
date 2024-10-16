from __future__ import annotations

from struct import unpack
from dataclasses import dataclass


@dataclass
class MixedPolygon:
    point_idx: list[int]
    uv: list[tuple[float, float]]
    norm: list[tuple[float, float, float]]


@dataclass
class IndexPolygon:
    point: list[int]
    uv: list[int]
    norm: list[int]


@dataclass
class Hmdl:
    points: list[tuple[float, float, float]]
    lines_idx: list[tuple[int, int]]
    polygons_mix: list[MixedPolygon]

    @staticmethod
    def load(path: str) -> Hmdl:
        this = Hmdl([], [], [])

        with open(path, "rb") as f:
            version = unpack("<I", f.read(4))[0]
            assert version == 204, f"Version mismatch: {version} != 204"

            (n_points, n_lines, n_triangles) = unpack("<III", f.read(3 * 4))
            print(f"{n_points = }, {n_lines = }, {n_triangles = }")

            for i in range(n_points):
                this.points.append(unpack("<fff", f.read(3 * 4)))

            for i in range(n_lines):
                this.lines_idx.append(unpack("<II", f.read(2 * 4)))

            for i in range(n_triangles):
                point_idx = list(unpack("<III", f.read(3 * 4)))

                norm_flat = unpack("<fffffffff", f.read(3 * 3 * 4))
                norm = [
                    tuple(norm_flat[i : i + 3]) for i in range(0, len(norm_flat), 3)
                ]

                uv_flat = unpack("<ffffff", f.read(3 * 2 * 4))
                uv = [tuple(uv_flat[i : i + 2]) for i in range(0, len(uv_flat), 2)]

                this.polygons_mix.append(MixedPolygon(point_idx, uv, norm))

        return this

    def to_obj(self) -> Obj:
        obj = Obj(self.points, [], [], [(a + 1, b + 1) for a, b in self.lines_idx], [])

        uvs_inv: dict[tuple[float, float], int] = {}
        norms_inv: dict[tuple[float, float, float], int] = {}

        for poly in self.polygons_mix:
            point_idx = [i + 1 for i in poly.point_idx]

            uv_idx = []
            for uv in poly.uv:
                try:
                    uv_idx.append(uvs_inv[uv])
                except KeyError:
                    i = len(uvs_inv) + 1
                    uvs_inv[uv] = i
                    uv_idx.append(i)
                    obj.uvs.append(uv)

            norm_idx = []
            for norm in poly.norm:
                try:
                    norm_idx.append(norms_inv[norm])
                except KeyError:
                    i = len(norms_inv) + 1
                    norms_inv[norm] = i
                    norm_idx.append(i)
                    obj.norms.append(norm)

            obj.polygons_idx.append(IndexPolygon(point_idx, uv_idx, norm_idx))

        return obj


@dataclass
class Obj:
    points: list[tuple[float, float, float]]
    uvs: list[tuple[float, float]]
    norms: list[tuple[float, float, float]]

    lines_idx: list[tuple[int, int]]
    polygons_idx: list[IndexPolygon]

    def save(self, path: str) -> None:
        with open(path, "w") as f:

            for v in self.points:
                f.write(f"v {v[0]} {v[1]} {v[2]}\n")
            f.write("\n")

            for vt in self.uvs:
                f.write(f"vt {vt[0]} {vt[1]}\n")
            f.write("\n")

            for vn in self.norms:
                f.write(f"vn {vn[0]} {vn[1]} {vn[2]}\n")
            f.write("\n")

            for l in self.lines_idx:
                f.write(f"l {l[0]} {l[1]}\n")
            f.write("\n")

            for p in self.polygons_idx:
                assert len(p.point) == len(p.uv) and len(p.point) == len(p.norm)
                f.write(f"f")
                for iv, ivt, ivn in zip(p.point, p.uv, p.norm):
                    f.write(f" {iv}/{ivt}/{ivn}")
                f.write("\n")
            f.write("\n")


if __name__ == "__main__":
    Hmdl.load("l200.hmdl").to_obj().save("l200.obj")
