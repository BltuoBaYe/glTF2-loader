#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace gltf2 {

using Attributes = std::unordered_map<std::string, uint32_t>;

struct Scene {
    std::string name;

    std::vector<uint32_t> nodes;

    // extensions / extras
};

struct Primitive {
    int32_t indices = -1; // Index to accessor containing the indices
    int32_t material = -1; // Index to the material

    enum class Mode : uint8_t {
        Points = 0,
        Lines = 1,
        LineLoop = 2,
        LineStrip = 3,
        Triangles = 4,
        TriangleStrip = 5,
        TriangleFan = 6
    } mode = Mode::Triangles; // primitive type

    Attributes attributes; // Each attribute is mapped with his name and accessor index to the data
    std::vector<Attributes> targets;

    // extensions / extras
};

struct Mesh {
    std::string name;

    std::vector<float> weights;
    std::vector<Primitive> primitives;

    // extensions / extras
};

struct Buffer {
    std::string name;

    std::string uri;
    uint32_t byteLength = 0;

    char* data = nullptr;

    // content

    // extensions / extras
};

struct BufferView {
    std::string name;

    uint32_t buffer; // Index to the buffer
    uint32_t byteOffset = 0;
    uint32_t byteLength = 0;
    uint32_t byteStride = 0; // The stride, in bytes

    enum class TargetType : uint16_t {
        None = 0,
        ArrayBuffer = 34962,
        ElementArrayBuffer = 34963
    } target; // The target that the GPU buffer should be bound to.

    // extensions / extras
};

/*struct Texture {
};

struct Sampler {
};

struct Image {
};*/

struct Material {
    std::string name;

    struct Texture {
        uint32_t index{0};
        uint32_t texCoord{0};
    };

    struct Pbr {
        float baseColorFactor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        Texture baseColorTexture;

        float metallicFactor{1.0f};
        float roughnessFactor{1.0f};
        Texture metallicRoughnessTexture;
    } pbr;

    struct NormalTexture : Texture {
        float scale{1.0f};
    } normalTexture;

    struct OcclusionTexture : Texture {
        float strength{1.0f};
    } occlusionTexture;

    Texture emissiveTexture;

    float emissiveFactor[3] = {0.0f, 0.0f, 0.0f};

    enum class AlphaMode : uint8_t {
        Opaque,
        Mask,
        Blend
    } alphaMode{AlphaMode::Opaque};

    float alphaCutoff{0.5f};
    bool doubleSided{false};
};

struct Node {
    std::string name;

    int32_t camera = -1;
    int32_t mesh = -1;
    int32_t skin = -1;

    std::vector<int> children;

    float matrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    float rotation[4] = {0, 0, 0, 1};
    float scale[3] = {1, 1, 1};
    float translation[3] = { 0, 0, 0 };

    std::vector<float> weights;

    // extensions / extras
};

struct Accessor {
    std::string name;

    int32_t bufferView = -1;
    uint32_t byteOffset = 0;

    enum class ComponentType : uint16_t {
        Byte = 5120,
        UnsignedByte = 5121,
        Short = 5122,
        UnsignedShort = 5123,
        UnsignedInt = 5125,
        Float = 5126
    } componentType;

    bool normalized = false;

    uint32_t count;

    enum class Type : uint8_t {
        Scalar,
        Vec2,
        Vec3,
        Vec4,
        Mat2,
        Mat3,
        Mat4
    } type;

    // max / min / sparse
    // extensions / extras
};

struct Asset {
    struct Metadata {
        std::string copyright;
        std::string generator;
        std::string version;
        std::string minVersion;

        // extensions / extras
    } metadata;

    std::vector<std::string> extensionsUsed;
    std::vector<std::string> extensionRequired;

    std::vector<Accessor> accessors;
    // std::vector<Animation> animations;
    std::vector<Buffer> buffers;
    std::vector<BufferView> bufferViews;
    // std::vector<Camera> cameras;
    // std::vector<Image> images;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    std::vector<Node> nodes;
    // std::vector<Sampler> samplers;
    int32_t scene = -1; // Index to the default scene
    std::vector<Scene> scenes;
    // std::vector<Skin> skins;
    // std::vector<Texture> textures;

    // extensions / extras

    std::string dirName;

    Scene* getDefaultScene() const;
};

/**
 * @brief      Load a glTF v2.0 asset from a file
 *
 * @param[in]  fileName  The file name
 *
 * @return     The asset
 */
Asset load(std::string fileName);
} // gltf2
