/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "Bomberman.hpp"

Point3D Map::getCameraRotation()
{
    return this->_cameraRotation;
}

Point3D Map::getCameraPosition()
{
    return this->_cameraPosition;
}

Point3D Map::getSpawnPoint(int player)
{
    return this->_spawnPoints.at(player);
}

std::vector<std::string *> *file_to_tab_str(int *size, char *str, std::vector<std::string *> *file)
{
    if (*size < 1 || (*size == 1 && str[0] == '\n'))
        str[0] = '\0';
    if (*size > 1) {
        if (str[*size - 1] == '\n')
            str[*size - 1] = '\0';
        else
            str[*size] = '\0';
    }
    if (*size != -1) {
        file->push_back(new std::string(str));
        free(str);
    }
    return file;
}

std::vector<std::string *> *file_to_tab(std::string path)
{
    FILE *fd = fopen(path.c_str(), "r");
    int size = 0;
    size_t bufsize = 0;
    char *buff;
    std::vector<std::string *> *file = new std::vector<std::string *>;

    size = 0;
    if (fd == NULL)
        return file;
    while (1) {
        size = getline(&buff, &bufsize, fd);
        file = file_to_tab_str(&size, buff, file);
        if (file->empty())
            return file;
        if (size == -1)
            break;
        bufsize = 0;
        size = 0;
    }
    return file;
}

std::vector<std::string> parse_a_block_str(std::string myBlockTab, int nbComma)
{
    int lastKeyComma = 0;
    std::vector<std::string> aBlockTab;

    for (size_t i = 0; i != nbComma; i += 1) {
        aBlockTab.push_back(myBlockTab.substr(lastKeyComma + 1, myBlockTab.find_first_of(';', lastKeyComma + 1) - (lastKeyComma + 1)));
        lastKeyComma = myBlockTab.find_first_of(';', lastKeyComma + 1);
    }
    aBlockTab.push_back(myBlockTab.substr(lastKeyComma + 1, myBlockTab.find_first_of(']', lastKeyComma + 1) - (lastKeyComma + 1)));
    return aBlockTab;
}

int countNbCommaBlockTab(std::string myBlockTab)
{
    int nbComma = 0;

    for (size_t i = 0; i != myBlockTab.size(); i += 1) {
        if (myBlockTab.at(i) == ';')
            nbComma++;
    }
    return nbComma;
}

std::vector<std::vector<std::string>> Map::parse_file_block_str_line(int j)
{
    std::vector<std::vector<std::string>> arrayX;

    size_t lastKey = -1;
    std::string myBlockTab;
    size_t nbComma = 0;
    size_t nbX = 0;

    for (size_t i = 0; i != this->_fileMap->at(j)->size(); i += 1) {
        if (this->_fileMap->at(j)->at(i) == ']')
            nbX++;
    }
    for (size_t i = 0; i != nbX; i += 1) {
        myBlockTab = this->_fileMap->at(j)->substr(lastKey + 1, this->_fileMap->at(j)->find_first_of(']', lastKey + 1) - (lastKey));
        lastKey = this->_fileMap->at(j)->find_first_of(']', lastKey + 1);
        nbComma = countNbCommaBlockTab(myBlockTab);
        arrayX.push_back(parse_a_block_str(myBlockTab, nbComma));
    }
    return arrayX;
}

void Map::parse_file_block_str()
{
    for (size_t j = 0; j != this->_fileMap->size(); j += 1) {
        this->_mapBlockYAxe.push_back(parse_file_block_str_line(j));
    }
}

void Map::parse_file_map()
{
    this->_fileMap = new std::vector<std::string *>();

    for (size_t i = 8; i != this->_file->size(); i += 1) {
        this->_fileMap->push_back(new std::string(*this->_file->at(i)));
    }
}

std::vector<std::vector<MapObj *>*> *Map::createMap_byFloor(int top, irr::f32 cY)
{
    irr::f32 cX = minX;
    irr::f32 cZ = minZ;
    MapObj *tmp;
    std::vector<MapObj *> *XObj = NULL;
    std::vector<std::vector<MapObj *>*> *ZObj = new std::vector<std::vector<MapObj *>*>();


    for (size_t i = 0; i != this->_mapBlockYAxe.size(); cZ -= 2.0f, i += 1) {
        XObj = new std::vector<MapObj *>();
        for (size_t j = 0; j != this->_mapBlockYAxe.at(i).size(); cX += 2.0f, j += 1) {
            if (top >= this->_mapBlockYAxe.at(i).at(j).size()) {
                tmp = new EmptyBlock(this->_gameObj);
                tmp->_type = ObjType::EmptyBlock;
                dynamic_cast<EmptyBlock *>(tmp)->init(Point3D{cX, cY, cZ});
                XObj->push_back(tmp);
            }
            else {
                if (this->_mapBlockYAxe.at(i).at(j).at(top) == "floor") {
                    tmp = new Floor(this->_gameObj);
                    tmp->_type = ObjType::Floor;
                    dynamic_cast<Floor *>(tmp)->init(Point3D{cX, cY, cZ});
                    XObj->push_back(tmp);
                }
                else if (this->_mapBlockYAxe.at(i).at(j).at(top) == "wall") {
                    tmp = new Wall(this->_gameObj);
                    tmp->_type = ObjType::Wall;
                    dynamic_cast<Wall *>(tmp)->init(Point3D{cX, cY, cZ});
                    XObj->push_back(tmp);
                }
                else if (this->_mapBlockYAxe.at(i).at(j).at(top) == "dblock") {
                    tmp = new DBlock(this->_gameObj);
                    tmp->_type = ObjType::DBlock;
                    dynamic_cast<DBlock *>(tmp)->init(Point3D{cX, cY, cZ});
                    XObj->push_back(tmp);
                }
                else if (this->_mapBlockYAxe.at(i).at(j).at(top) == "empty") {
                    tmp = new EmptyBlock(this->_gameObj);
                    tmp->_type = ObjType::EmptyBlock;
                    dynamic_cast<EmptyBlock *>(tmp)->init(Point3D{cX, cY, cZ});
                    XObj->push_back(tmp);
                }
                else {
                    tmp = new EmptyBlock(this->_gameObj);
                    tmp->_type = ObjType::EmptyBlock;
                    dynamic_cast<EmptyBlock *>(tmp)->init(Point3D{cX, cY, cZ});
                    XObj->push_back(tmp);
                }
            }
        }
        cX = minX;
        ZObj->push_back(XObj);
    }
    return ZObj;
}

void Map::createMap()
{
    int top = 0;
    irr::f32 cY = minY;

    parse_file_map();
    parse_file_block_str();
    for (size_t i = 0; i != this->_maxTop; cY += 2.0f, top++, i += 1) {
        this->_objArray->push_back(createMap_byFloor(top, cY));
    }
}

Point3D Map::getSpawnPointFromFileMap(std::string &spStr)
{
    Point3D sp;
    std::string p;
    int nbComma = 0;
    size_t i = 0;

    spStr.erase(0, 1);
    spStr.erase(spStr.size() - 1, 1);
    for (size_t k = 0; k != spStr.size(); k += 1) {
        if (spStr.at(k) == ';')
            nbComma++;
    }
    if (nbComma != 2) {
        std::cerr << "Bad File Map: bad spawn point values" << std::endl;
        exit(84);
    }
    for (i = 0; spStr.at(i) != ';'; i += 1) {
        if ((spStr.at(i) < '0' || spStr.at(i) > '9') && spStr.at(i) != '-') {
            std::cerr << "Bad File Map: bad spawn point values" << std::endl;
            exit(84);
        }
        p.push_back(spStr.at(i));
    }
    sp.x = atoi(p.c_str());
    for (i++, p.clear(); spStr.at(i) != ';'; i += 1) {
        if ((spStr.at(i) < '0' || spStr.at(i) > '9') && spStr.at(i) != '-') {
            std::cerr << "Bad File Map: bad spawn point values" << std::endl;
            exit(84);
        }
        p.push_back(spStr.at(i));
    }
    sp.y = atoi(p.c_str());
    for (i++, p.clear(); i != spStr.size(); i += 1) {
        if ((spStr.at(i) < '0' || spStr.at(i) > '9') && spStr.at(i) != '-') {
            std::cerr << "Bad File Map: bad spawn point values" << std::endl;
            exit(84);
        }
        p.push_back(spStr.at(i));
    }
    sp.z = atoi(p.c_str());
    return sp;
}

void Map::errorMapManage_spawnPoint()
{
    std::string spawnPointStr;
    std::string spawnPointStrV;

    for (size_t i = 3; i != 7; i += 1) {
        if (this->_file->at(i)->size() < 20) {
            std::cerr << "Bad File Map: spawn-point invalid" << std::endl;
            exit(84);
        }
    }
    for (size_t i = 3; i != 7; i += 1) {
        spawnPointStr = this->_file->at(i)->substr(0, 11);
        if (spawnPointStr != "spawn-point") {
            std::cerr << "Bad File Map: Line " << i << " is not a valid spawn-point" << std::endl;
            exit(84);
        }
    }
    for (size_t i = 3; i != 7; i += 1) {
        spawnPointStrV = this->_file->at(i)->substr(13);
        if (spawnPointStrV.at(0) != '[' || spawnPointStrV.at(spawnPointStrV.size() - 1) != ']') {
            std::cerr << "Bad File Map: Line " << i << "is not a valid spawn-point (missing [])" << std::endl;
            exit(84);
        }
        this->_spawnPointsBrut.push_back(getSpawnPointFromFileMap(spawnPointStrV));
    }
}

Point3D Map::getCameraRotFromFileMap(std::string &cmStr)
{
    size_t i = 0;
    int nbComma = 0;
    Point3D cmR;
    std::string p;

    cmStr.erase(0, 1);
    cmStr.erase(cmStr.size() - 1, 1);

    for (size_t k = 0; k != cmStr.size(); k += 1) {
        if (cmStr.at(k) == ';')
            nbComma++;
    }
    if (nbComma != 2) {
        std::cerr << "Bad File Map: bad camera rotation values" << std::endl;
        exit(84);
    }
    for (i = 0; cmStr.at(i) != ';'; i += 1) {
        if ((cmStr.at(i) < '0' || cmStr.at(i) > '9') && cmStr.at(i) != '-' && cmStr.at(i) != '.') {
            std::cerr << "Bad File Map: bad camera rotation values" << std::endl;
            exit(84);
        }
        p.push_back(cmStr.at(i));
    }
    cmR.x = std::stof(p);
    for (i++, p.clear(); cmStr.at(i) != ';'; i += 1) {
        if ((cmStr.at(i) < '0' || cmStr.at(i) > '9') && cmStr.at(i) != '-' && cmStr.at(i) != '.') {
            std::cerr << "Bad File Map: bad camera rotation values" << std::endl;
            exit(84);
        }
        p.push_back(cmStr.at(i));
    }
    cmR.y = std::stof(p);
    for (i++, p.clear(); i != cmStr.size(); i += 1) {
        if ((cmStr.at(i) < '0' || cmStr.at(i) > '9') && cmStr.at(i) != '-' && cmStr.at(i) != '.') {
            std::cerr << "Bad File Map: bad camera rotation values" << std::endl;
            exit(84);
        }
        p.push_back(cmStr.at(i));
    }
    cmR.z = std::stof(p);

    std::cout << "x: " << cmR.x << " y: " << cmR.y << " z: " << cmR.z << std::endl;
    return cmR;
}

void Map::errorMapManage_cameraRot()
{
    std::string cameraRotStr;
    std::string cameraRotStrV;

    if (this->_file->at(2)->size() < 23) {
        std::cerr << "Bad File Map: camera-rotation invalid" << std::endl;
        exit(84);
    }
    cameraRotStr = this->_file->at(2)->substr(0, 15);
    if (cameraRotStr != "camera-rotation") {
        std::cerr << "Bad File Map: Line " << 2 << " is not a valid camera-rotation" << std::endl;
        exit(84);
    }
    cameraRotStrV = this->_file->at(2)->substr(16);
    if (cameraRotStrV.at(0) != '[' || cameraRotStrV.at(cameraRotStrV.size() - 1) != ']') {
        std::cerr << "Bad File Map: Line " << 2 << "is not a valid camera-rotation (missing [])" << std::endl;
        exit(84);
    }
    this->_cameraRotation = getCameraRotFromFileMap(cameraRotStrV);
}

Point3D Map::getCameraPosFromFileMap(std::string &cmStr)
{
    size_t i = 0;
    int nbComma = 0;
    Point3D cmP;
    std::string p;

    cmStr.erase(0, 1);
    cmStr.erase(cmStr.size() - 1, 1);

    for (size_t k = 0; k != cmStr.size(); k += 1) {
        if (cmStr.at(k) == ';')
            nbComma++;
    }
    if (nbComma != 2) {
        std::cerr << "Bad File Map: bad camera position values" << std::endl;
        exit(84);
    }
    for (i = 0; cmStr.at(i) != ';'; i += 1) {
        if ((cmStr.at(i) < '0' || cmStr.at(i) > '9') && cmStr.at(i) != '-' && cmStr.at(i) != '.') {
            std::cerr << "Bad File Map: bad camera position values" << std::endl;
            exit(84);
        }
        p.push_back(cmStr.at(i));
    }
    cmP.x = std::stof(p);
    for (i++, p.clear(); cmStr.at(i) != ';'; i += 1) {
        if ((cmStr.at(i) < '0' || cmStr.at(i) > '9') && cmStr.at(i) != '-' && cmStr.at(i) != '.') {
            std::cerr << "Bad File Map: bad camera position values" << std::endl;
            exit(84);
        }
        p.push_back(cmStr.at(i));
    }
    cmP.y = std::stof(p);
    for (i++, p.clear(); i != cmStr.size(); i += 1) {
        if ((cmStr.at(i) < '0' || cmStr.at(i) > '9') && cmStr.at(i) != '-' && cmStr.at(i) != '.') {
            std::cerr << "Bad File Map: bad camera position values" << std::endl;
            exit(84);
        }
        p.push_back(cmStr.at(i));
    }
    cmP.z = std::stof(p);

    std::cout << "x: " << cmP.x << " y: " << cmP.y << " z: " << cmP.z << std::endl;
    return cmP;
}

void Map::errorMapManage_cameraPos()
{
    std::string cameraPosStr;
    std::string cameraPosStrV;

    if (this->_file->at(1)->size() < 23) {
        std::cerr << "Bad File Map: camera-position invalid" << std::endl;
        exit(84);
    }
    cameraPosStr = this->_file->at(1)->substr(0, 15);
    if (cameraPosStr != "camera-position") {
        std::cerr << "Bad File Map: Line " << 1 << " is not a valid camera-postion" << std::endl;
        exit(84);
    }
    cameraPosStrV = this->_file->at(1)->substr(16);
    if (cameraPosStrV.at(0) != '[' || cameraPosStrV.at(cameraPosStrV.size() - 1) != ']') {
        std::cerr << "Bad File Map: Line " << 1 << "is not a valid camera-position (missing [])" << std::endl;
        exit(84);
    }
    this->_cameraPosition = getCameraPosFromFileMap(cameraPosStrV);
}

void Map::errorMapManage_camera()
{
    errorMapManage_cameraPos();
    errorMapManage_cameraRot();
}

void Map::errorMapManage_maxTop()
{
    std::string maxTopStrV;
    std::string maxTopStr;

    if (this->_file->at(0)->size() < 9) {
        std::cerr << "Bad File Map: missing max-top" << std::endl;
        exit(84);
    }
    maxTopStrV = this->_file->at(0)->substr(0, 8);
    if (maxTopStrV != "max-top:") {
        std::cerr << "Bad File Map: missing max-top" << std::endl;
        exit(84);
    }
    maxTopStrV = this->_file->at(0)->substr(8);
    for (size_t i = 0; i != maxTopStrV.size(); i += 1) {
        if ((maxTopStrV.at(i) < '0' || maxTopStrV.at(i) > '9') && maxTopStrV.at(i) != '-') {
            std::cerr << "Bad File Map: max-top value is invalid" << std::endl;
            exit(84);
        }
    }
    this->_maxTop = atoi(maxTopStrV.c_str());

}

void Map::errorMapManage()
{
    if (this->_file->size() < 9) {
        std::cerr << "Bad File Map" << std::endl;
        exit(84);
    }
    if (this->_file->at(7)->size() != 0) {
        std::cerr << "Bad File Map" << std::endl;
        exit(84);
    }
    errorMapManage_maxTop(); 
    errorMapManage_camera();
    errorMapManage_spawnPoint();
}

void Map::hello()
{
    std::cout << "Hello" << std::endl;
} 

void Map::init(std::string path)
{
    Point3D cp;

    this->_objArray = new mapObj3DArray();
    this->_file = file_to_tab(path);
    errorMapManage();
    createMap();
    for (size_t i = 0; i != this->_spawnPointsBrut.size(); i += 1) {
        cp = this->_objArray->at(this->_spawnPointsBrut.at(i).y)->at(this->_spawnPointsBrut.at(i).z)->at(this->_spawnPointsBrut.at(i).x)->getPosition();
        this->_spawnPoints.push_back({cp.x, cp.y += 2.3f, cp.z});
    }
}

Map::Map()
{
}

Map::~Map()
{
}
