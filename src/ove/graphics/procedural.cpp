#include "procedural.hpp"

#include <ove/math/consts.hpp>

namespace graphics {
namespace procedural {

    namespace wire {

        void genPlane(vertex_array_t& data, vec2f size)
        {
            const f32 vdata[] = { size.x, size.y, 0.f, size.x, -size.y, 0.f,
                -size.x, size.y, 0.f, -size.x, -size.y, 0.f };

            const u32 edata[] = { 0, 1, 1, 3, 2, 3, 2, 0 };

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.emplace_back(3);
        }

        void genBox(vertex_array_t& data, vec3f min, vec3f max)
        {
            const f32 vdata[] = { min.x, min.y, min.z, max.x, min.y, min.z, min.x, max.y,
                min.z, max.x, max.y, min.z, min.x, min.y, max.z, max.x,
                min.y, max.z, min.x, max.y, max.z, max.x, max.y, max.z };

            const u32 edata[] = { 0, 1, 3, 1, 2, 0, 2, 3, 4, 5, 7, 5,
                6, 4, 6, 7, 0, 4, 1, 5, 2, 6, 3, 7 };

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.emplace_back(3);
        }

        void genShpere(vertex_array_t& data, f32 r, u32 segments)
        {
            f32 vdata[segments * 9];
            u32 edata[segments * 6];

            u32 idx1 = 0;
            u32 idx2 = 0;

            const u32 i1 = 0;
            const u32 i2 = 1 * segments;
            const u32 i3 = 2 * segments;

            const u32 i13 = i1 * 3;
            const u32 i23 = i2 * 3;
            const u32 i33 = i3 * 3;

            const u32 i12 = i1 * 2;
            const u32 i22 = i2 * 2;
            const u32 i32 = i3 * 2;

            for (u32 i = 0; i < segments; ++i) {
                const f32 angle = ((f32)i / (segments - 1)) * 2 * pi<f32>();
                const f32 x = std::cos(angle) * r;
                const f32 y = std::sin(angle) * r;

                vdata[i13 + idx1] = x;
                vdata[i13 + idx1 + 1] = y;
                vdata[i13 + idx1 + 2] = 0;

                vdata[i23 + idx1] = x;
                vdata[i23 + idx1 + 1] = 0;
                vdata[i23 + idx1 + 2] = y;

                vdata[i33 + idx1] = 0;
                vdata[i33 + idx1 + 1] = x;
                vdata[i33 + idx1 + 2] = y;

                edata[i12 + idx2] = i1 + i;
                edata[i12 + idx2 + 1] = (i1 + i + 1) >= (i1 + segments) ? i1 : (i1 + i + 1);

                edata[i22 + idx2] = i2 + i;
                edata[i22 + idx2 + 1] = (i2 + i + 1) >= (i2 + segments) ? i2 : (i2 + i + 1);

                edata[i32 + idx2] = i3 + i;
                edata[i32 + idx2 + 1] = (i3 + i + 1) >= (i3 + segments) ? i3 : (i3 + i + 1);

                idx1 += 3;
                idx2 += 2;
            }

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.emplace_back(3);
        }
    }

    namespace unlit {
        void genPlane(vertex_array_t& data, vec2f size)
        {
            const f32 vdata[] = { size.x, size.y, size.x, -size.y,
                -size.x, size.y, -size.x, -size.y };

            const u32 edata[] = { 0, 1, 2, 1, 2, 3 };

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.reserve(3);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(2);
        }

        void genCube(vertex_array_t& data, vec3f min, vec3f max)
        {
            const f32 vdata[] = {
                min.x, min.y, min.z, // -,-,-
                max.x, min.y, min.z, // +,-,-
                min.x, max.y, min.z, // -,+,-
                max.x, max.y, min.z, // +,+,-
                min.x, min.y, max.z, // -,-,+
                max.x, min.y, max.z, // +,-,+
                min.x, max.y, max.z, // -,+,+
                max.x, max.y, max.z // +,+,+
            };

            const u32 edata[] = {
                0, 2, 1, 1, 2, 3, // near
                4, 5, 7, 4, 7, 6, // far
                6, 3, 2, 6, 7, 3, // top
                0, 1, 5, 0, 5, 4, // bottom
                1, 3, 7, 5, 1, 7, // left
                6, 0, 4, 6, 2, 0 // right
            };

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.emplace_back(3);
        }
    }

    namespace lit {
        void genPlane(vertex_array_t& data, vec2f size)
        {
            const f32 vdata[] = {
                size.x, size.y, 0.f, 0, 1, 0, 1, 1, // +,+
                size.x, -size.y, 0.f, 0, 1, 0, 1, 0, // +,-
                -size.x, size.y, 0.f, 0, 1, 0, 0, 1, // -,+
                -size.x, -size.y, 0.f, 0, 1, 0, 0, 0 // -,-
            };

            const u32 edata[] = { 0, 1, 2, 1, 2, 3 };

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.reserve(3);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(2);
        }

        void genCube(vertex_array_t& data, vec3f min, vec3f max)
        {
            const f32 vdata[] = {
                // left
                min.x, min.y, min.z, -1, 0, 0, 0, 0, -1, 0, 0, // -,-,-
                min.x, max.y, min.z, -1, 0, 0, 0, 0, -1, 0, 1, // -,+,-
                min.x, min.y, max.z, -1, 0, 0, 0, 0, -1, 1, 0, // -,-,+
                min.x, max.y, max.z, -1, 0, 0, 0, 0, -1, 1, 1, // -,+,+

                // right
                max.x, min.y, min.z, 1, 0, 0, -1, 0, 0, 0, 0, // +,-,-
                max.x, max.y, min.z, 1, 0, 0, -1, 0, 0, 0, 1, // +,+,-
                max.x, min.y, max.z, 1, 0, 0, -1, 0, 0, 1, 0, // +,-,+
                max.x, max.y, max.z, 1, 0, 0, -1, 0, 0, 1, 1, // +,+,+

                // top
                min.x, max.y, min.z, 0, 1, 0, -1, 0, 0, 0, 0, // -,+,-
                min.x, max.y, max.z, 0, 1, 0, -1, 0, 0, 0, 1, // -,+,+
                max.x, max.y, min.z, 0, 1, 0, -1, 0, 0, 1, 0, // +,+,-
                max.x, max.y, max.z, 0, 1, 0, -1, 0, 0, 1, 1, // +,+,+

                // bottom
                min.x, min.y, min.z, 0, -1, 0, 1, 0, 0, 0, 0, // -,-,-
                min.x, min.y, max.z, 0, -1, 0, 1, 0, 0, 0, 1, // -,-,+
                max.x, min.y, min.z, 0, -1, 0, 1, 0, 0, 1, 0, // +,-,-
                max.x, min.y, max.z, 0, -1, 0, 1, 0, 0, 1, 1, // +,-,+

                // near
                min.x, min.y, min.z, 0, 0, -1, -1, 0, 0, 0, 0, // -,-,-
                min.x, max.y, min.z, 0, 0, -1, -1, 0, 0, 0, 1, // -,+,-
                max.x, min.y, min.z, 0, 0, -1, -1, 0, 0, 1, 0, // +,-,-
                max.x, max.y, min.z, 0, 0, -1, -1, 0, 0, 1, 1, // +,+,-

                // far
                min.x, min.y, max.z, 0, 0, 1, 1, 0, 0, 0, 0, // -,-,+
                min.x, max.y, max.z, 0, 0, 1, 1, 0, 0, 0, 1, // -,+,+
                max.x, min.y, max.z, 0, 0, 1, 1, 0, 0, 1, 0, // +,-,+
                max.x, max.y, max.z, 0, 0, 1, 1, 0, 0, 1, 1, // +,+,+
            };

            const u32 edata[] = {
                0, 2, 1, 1, 2, 3, // left
                4, 5, 6, 6, 5, 7, // right
                8, 9, 10, 10, 9, 11, // top
                12, 14, 13, 13, 14, 15, // bottom
                16, 17, 18, 18, 17, 19, // near
                20, 22, 21, 21, 22, 23, // far
            };

            data.vertices = vertex_data(vdata, vdata + (sizeof(vdata) / sizeof(f32)));
            data.elements = element_data(edata, edata + (sizeof(edata) / sizeof(u32)));
            data.attributes.clear();
            data.attributes.reserve(4);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(3);
            data.attributes.emplace_back(2);
        }
    }

}
}
