/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <stdio.h>
#include <string>
#include <vector>

#include "irrlicht.h"
#include "event.hpp"
#include "Music.hpp"

#define minX 0
#define maxX 30
#define minY 0
#define maxY 30
#define minZ 0
#define maxZ 30

typedef struct Point2D_s Point2D;       //Les structures sont acessibles partout dans le header
typedef struct Rect2D_s Rect2D;
typedef struct Point3D_s Point3D;
typedef struct Rect3D_s Rect3D;
typedef struct configBomberman_s configBomberman_t;
typedef struct KeyLayout_s KeyLayout;

class Bomb;
class BombUp;
class Bomberman;
class BombermanIA;
class Camera;
class DBlock;
class EmptyBlock;
class Fireball;
class FireUp;
class GameObject;        //Les classes sont acessibles partout dans le header (Forwarding Declaration)
class Map;
class MapObj;
class SpeedUp;
class Wall;
class WallPass;

enum class Direction;
enum class ObjType;

typedef std::vector<std::vector<std::vector<MapObj *>*>*> mapObj3DArray; //Voilà quoi (lisibilité). C'est un array d'objets en 3D (z/y/x)

struct Point2D_s
{
    int x;
    int y;
};

struct Rect2D_s
{
    int x;
    int size_x;
    int y;
    int size_y;
};

struct Point3D_s
{
    irr::f32 x; //Expl 200
    irr::f32 y; //Expl 300
    irr::f32 z; //Expl 50
};

struct Rect3D_s
{
    irr::f32 x; //Expl 0
    irr::f32 size_x; //Expl 200
    irr::f32 y; //Expl 0
    irr::f32 size_y; //Expl 300
    irr::f32 z; //Expl 0
    irr::f32 size_z; //Expl 100
};

struct configBomberman_s
{
    ObjType BombermanOne;
    ObjType BombermanTwo;
    std::wstring BombermanOneName;
    std::wstring BombermanTwoName;
};

struct KeyLayout_s
{
    irr::EKEY_CODE Up;
    irr::EKEY_CODE Down;
    irr::EKEY_CODE Left;
    irr::EKEY_CODE Right;
    irr::EKEY_CODE SetBomb;
};

enum class Direction
{
    None = -1,
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3,
};

enum class ObjType
{
    Bomberman = 0,
    BombermanIA = 1,
    Bomb = 2,
    Wall = 3,
    EmptyBlock = 4,
    DBlock = 5,
    Floor = 6,
    SpeedUp = 7,
    BombUp = 8,
    FireUp = 9,
    WallPass = 10,
};

class MapObj
{
    public:
    //functions
        MapObj() = default;
        virtual ~MapObj() = default;
        virtual Point3D getPosition() = 0;
        // Getters et Setters supplémentaires ...
    //data
        GameObject *_gameObj;
        ObjType _type;
    private:
    //functions
    //data
};

class Floor : public MapObj //Sol (À compléter au fur et à mesure)
{
    public:
    //functions
        Floor(GameObject *gmo);
        virtual ~Floor();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires ...
    //data
    private:
    //functions
    //data
        int _id;
        Point3D _pos;
        Rect3D _rect;
        IAnimatedMeshSceneNode *_sprite;
        bool _isAlive;    
};

class Wall : public MapObj //Murs incassables. Trouvés aux bords de la map par exemple. (À compléter au fur et à mesure)
{
    public:
    //functions
        Wall(GameObject *gmo);
        virtual ~Wall();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        void destroyAnim();
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires ...
    //data
    private:
    //functions
    //data
        int _id;
        Point3D _pos;
        Rect3D _rect;
        IAnimatedMeshSceneNode *_sprite;
        bool _isAlive;
};

class EmptyBlock : public MapObj //Blocks vides. C'est un objet comme un autre sauf qu'il est vide (À compléter au fur et à mesure)
{
    public:
    //functions
        EmptyBlock(GameObject *gmo);
        virtual ~EmptyBlock();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        Point3D getPosition();
        Rect3D getRect();
        // Getters et Setters supplémentaires ...
    //data
    private:
    //functions
    //data
        int _id;
        Point3D _pos;
        Rect3D _rect;
        IAnimatedMeshSceneNode *_sprite;
};

class DBlock : public MapObj //Blocks qui peuvent se détruire (À compléter au fur et à mesure)
{
    public:
    //functions
        DBlock(GameObject *gmo);
        virtual ~DBlock();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        void destroyAnim();
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires ...
    //data
    private:
    //functions
    //data
        int _id;
        Point3D _pos;
        Rect3D _rect;
        IAnimatedMeshSceneNode *_sprite;
};

class SpeedUp : public MapObj //Bonus permettant au joueur et aux IA d'aller + vite (À compléter au fur et à mesure)
{
    public:
    //functions
        SpeedUp(GameObject *gmo);
        virtual ~SpeedUp();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        int getSpeed();
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires
    //data
    private:
    //functions
    //data
        int _id;
        bool _isAlive;
        int _speed;
        Point3D _pos;
        Rect3D _rect;
};

class BombUp : public MapObj //rajoute une bombe dans l'inventaire du Joueur ou de l'IA (À compléter au fur et à mesure)
{
    public:
    //functions
        BombUp(GameObject *gmo);
        virtual ~BombUp();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        int getBonusBomb();
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires
    //data
    private:
    //functions
    //data
        int _id;
        bool _isAlive;
        int _nbAddBomb;
        Point3D _pos;
        Rect3D _rect;
};

class FireUp : public MapObj //Rajoute Une case de plus dans le radius de la bombe (À compléter au fur et à mesure)
{
    public:
    //functions
        FireUp(GameObject *gmo);
        virtual ~FireUp();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        Rect3D getRadius();
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires
    //data
    private:
    //functions
    //data
        int _id;
        bool _isAlive;
        Rect3D _radius;
        Point3D _pos;
        Rect3D _rect;
};

class WallPass : public MapObj //Bonus qui permet de faire passer la bombe au dessus de n'importe quel mur (Même le mur de Trump ..) (À compléter au fur et à mesure)
{
    public:
    //functions
        WallPass(GameObject *gmo);
        virtual ~WallPass();
        void init(Point3D pos);
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        Point3D getPosition();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires
    //data
    private:
    //functions
    //data
        int _id;
        bool _isAlive;
        Point3D _pos;
        Rect3D _rect;
};

class Map //Regroupe tous les blocks du jeu (À compléter au fur et à mesure)
{
    public:
    //functions
        Map();
        ~Map();
        void init(std::string filePath);
        mapObj3DArray getMap();
        std::vector<std::string *> *getFileMap();
        Point3D getSpawnPoint(int player);
        Point3D getCameraPosition();
        Point3D getCameraRotation();
        void hello(void);
        // Getters et Setters supplémentaires
    //data
        GameObject *_gameObj;
    private:
    //functions
        std::vector<std::vector<std::string>> parse_file_block_str_line(int j);
        void parse_file_block_str();
        void parse_file_map();
        Point3D getSpawnPointFromFileMap(std::string &spStr);
        Point3D getCameraRotFromFileMap(std::string &cmStr);
        Point3D getCameraPosFromFileMap(std::string &cmStr);
        void errorMapManage_spawnPoint();
        void errorMapManage_cameraRot();
        void errorMapManage_cameraPos();
        void errorMapManage_camera();
        void errorMapManage_maxTop();
        void errorMapManage();
        std::vector<std::vector<MapObj *>*> *createMap_byFloor(int top, irr::f32 cY);
        void createMap();
    //data
        std::vector<std::string *> *_file;
        std::vector<std::string *> *_fileMap;
        std::vector<std::vector<std::vector<std::string>>> _mapBlockYAxe;
        mapObj3DArray *_objArray;
        int _maxTop;
        std::vector<Point3D> _spawnPointsBrut;
        std::vector<Point3D> _spawnPoints;
        Point3D _cameraPosition;
        Point3D _cameraRotation;
};

class Fireball
{
    public:
    //functions
        Fireball(GameObject *gmo);
        ~Fireball();
        void init(Point3D pos);
        void destroy();
        bool isSet();
    //data
        GameObject *_gameObj;
    private:
    //functions
    //data
        Point3D _pos;
        Point3D _scale;
        IAnimatedMeshSceneNode* _sprite;
};

class Bomb //Les bombes que peuvent balancer Bomberman et les IA (À compléter au fur et à mesure)
{
    public:
    //functions
        Bomb(GameObject *);
        ~Bomb();
        void compute();
        void init(Point3D pos, int radius);
        void destroy();
        bool hit(Direction dir, Point3D far, Point3D posSrc, Rect3D rectSrc);
        bool isSet();
        bool isExplode();
        // Getters et Setters supplémentaires ...
    //data
        GameObject *_gameObj;
    private:
    //functions
        void compute_fireball();
        void destroy_fireball();
    //data
        Point3D _pos;
        Point3D _scale;
        int _radius;
        IAnimatedMeshSceneNode* _sprite;
        std::vector<Fireball *> _fireballs_left;
        std::vector<Fireball *> _fireballs_right;
        std::vector<Fireball *> _fireballs_forward;
        std::vector<Fireball *> _fireballs_backward;
        irr::u32 _explodeTimer;
        irr::u32 _animTimer;
        Music *_sound;
        bool _playSound;
        bool _explode;
        bool _isInit;
};

class BombermanIA //Les IA se déplacent sur la map (À compléter au fur et à mesure)
{
    public:
    //functions
        BombermanIA();
        ~BombermanIA();
        void init(std::wstring name, Point3D pos);
        int compute(); //À partir de cette fonction, l'ia va réfléchir et faire les actions désirés pour un tour de boucle
        int draw();
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        Point3D getPos();
        Rect3D getRect();
        bool isAlive();
        // Getters et Setters supplémentaires ...
    //data
        GameObject *_gameObj;
    private:
    //functions
        int move(); //Ceci est un exemple de fonction (À modifier)
        int moveLeft(); //Ceci est un exemple de fonction (À modifier)
        int moveRight(); //Ceci est un exemple de fonction (À modifier)
        int moveUp(); //Ceci est un exemple de fonction (À modifier)
        int moveDown(); //Ceci est un exemple de fonction (À modifier)
        bool setBombAt(Point3D *pos); //Ceci est un exemple de fonction (À modifier)
    //data
        std::wstring _name;
        Point3D _pos;
        Rect3D _rect;
        std::vector<Bomb *> _bombs;
        IAnimatedMeshSceneNode* _sprite;
        int maxBomb;
        bool _isAlive;
};

class Bomberman //Le joueur ou les joueurs (À compléter au fur et à mesure)
{
    public:
    //functions
        Bomberman();
        ~Bomberman();
        void init(std::wstring name, Point3D pos, KeyLayout keyLayout);
        int compute(MyEventReceiver *event); //À partir de cette fonction, le joueur va réfléchir en fonction de la touche et va faire les actions désirés pour un tour de boucle
        bool hit(Direction *dir, Point3D *far, Point3D *posSrc, Rect3D *rectSrc);
        Point3D getPos();
        Rect3D getRect();
        Direction getCurrentDir();
        bool isAlive();
        // Getters et Setters supplémentaires ...
    //data
        GameObject *_gameObj;
    private:
    //functions
        void compute_bomb();
        void compute_keySetBomb(MyEventReceiver *event);
        void move(Direction dir, irr::f32 speed); //Ceci est un exemple de fonction (À modifier)
        void moveLeft(irr::f32 speed); //Ceci est un exemple de fonction (À modifier)
        void moveRight(irr::f32 speed); //Ceci est un exemple de fonction (À modifier)
        void moveUp(irr::f32 speed); //Ceci est un exemple de fonction (À modifier)
        void moveDown(irr::f32 speed); //Ceci est un exemple de fonction (À modifier)
        void setBombAt(Point3D pos); //Ceci est un exemple de fonction (À modifier)
    //data
        std::wstring _name;
        Point3D _pos;
        Point3D _rot;
        Rect3D _rect;
        Direction _currentDir;
        std::vector<Bomb *> _bombs;
        IAnimatedMeshSceneNode* _sprite;
        KeyLayout _keyLayout;
        bool _pressSetBomb;
        bool _isAlive;
};

class Camera
{
    public:
    //functions
        Camera();
        ~Camera();
        void init(Point3D pos, Point3D rot);
        void compute(MyEventReceiver *event);
    //data
        GameObject *_gameObj;
    private:
    //fonctions
        void setKeyMap();
    //data
        ICameraSceneNode *camera;
        SKeyMap keyMap[5];
        Point3D _pos;
        Point3D _rot;

};

class GameObject
{
    public:
    //functions
        GameObject(IrrlichtDevice *device, configBomberman_t *cf);
        ~GameObject();
        void createPool();
        void init(int selected_map);
    //data
        IrrlichtDevice *_device;
        IVideoDriver *_videoDriver;
        ISceneManager *_sceneManager;
        IGUIEnvironment *_gui;
        irr::ITimer *_timer;
        configBomberman_t *_configBbmCharacter;
        std::vector<BombermanIA *> _ia;
        std::vector<Bomberman *> _player;
        Camera *_camera;
        Map *_map;
    private:
    //functions
        void createBombermanWithType();
        void initBombermanWithType();
    //data
};

class Game {
    public:
    //functions
        Game(IrrlichtDevice *device, configBomberman_t *cf, int selected_map);
        ~Game();
        int update(MyEventReceiver *event);
    //data
    private:
    //functons
    //data
        GameObject *gameObj;
        IrrlichtDevice *device;
        IVideoDriver *videoDriver;
        ISceneManager *sceneManager;
        IGUIEnvironment *gui;
        MyEventReceiver *eventReceiver;
        configBomberman_t *config;
        bool isSet;
};

#endif /* !BOMBERMAN_HPP_ */
