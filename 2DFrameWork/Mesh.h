#pragma once
class Mesh
{
    friend class GameObject;
    friend class Collider;
private:
    ID3D11Buffer*           vertexBuffer;
    ID3D11Buffer*           indexBuffer;

    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
    VertexType              vertexType;
    UINT                    byteWidth;

 
public:
    UINT* indices;
    UINT                    indexCount;
    void* vertices;
    UINT                    vertexCount;
    string                  file;
public:
    Mesh();
    ~Mesh();
    void Set();
    void LoadFile(string file);
    void SaveFile(string file);
    void Reset();
};

