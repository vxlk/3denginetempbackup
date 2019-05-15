#include "../pch.h"

enum class OBJECT_TYPE
{
	OBJ
};

struct ObjObject
{
	//Object Params
	std::vector<Vector3>		m_vertices;
	std::vector<Vector2>		m_uvs;
	std::vector<Vector3>		m_normals;
	
	//VBO index
	std::vector<unsigned short> m_indices;
	std::vector<Vector3>		m_indexed_vertices;
	std::vector<Vector2>		m_indexed_uvs;
	std::vector<Vector3>		m_indexed_normals;

	bool indexIsOkay = false; //set true if VBO has been indexed
	bool loadedOkay  = false; //set true if successfully loaded
};

class ObjLoader
{

public:
	static ObjObject loadOBJ(const std::string& filePath);
	static void      indexVBO_OBJ(ObjObject& objectToBeMODIFIED);
};

/*
Wrapper class for all types of objects -> CAN ONLY CONTAIN ONE TYPE AT A TIME
you can then load the object into the wrapper and use it in the code -> it sets the type on construction
this avoids making multiple functions for every type of objects -> they will all
be handled in one class
*/
class Object
{
	std::shared_ptr<ObjObject> m_objObject;
	OBJECT_TYPE m_typeOfObject; //set on construction

public:
	Object(ObjObject objectToBeLoaded);

	constexpr OBJECT_TYPE getObjectType() { return m_typeOfObject; }
};