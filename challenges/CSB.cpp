#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

#define PI 3.14159265
#define EPSILON 0.00000001
class Vector2D
{
    protected:
        float m_x;
        float m_y;
    public:
        Vector2D(float x = 0.0, float y = 0.0)
        {
            m_x = x;
            m_y = y;
        }
        ~Vector2D(){}
        //update class
        void setVector2D(float x = 0.0, float y = 0.0)
        {
            m_x = x;
            m_y = y;
        }
        float x() const
        {
            return m_x;
        }
        float y() const
        {
            return m_y;
        }
        //update attr m_x
        void setX(float x)
        {
            m_x = x;
        }
        //update attr m_y
        void setY(float y)
        {
            m_y = y;
        }
        //tron
        void Truncate(float upperBound)
        {
            float sqrLen = length();
            if(sqrLen > upperBound * upperBound)
            {
                float mult = upperBound/sqrt(sqrLen);
                m_x *= mult; m_y *= mult;
            }
        }
        float length() const //retourne l'intensité vectoriel
        {
            return sqrt((m_x * m_x) + (m_y * m_y));
        }
        float lengthSquared() const//retourne l"intensité au carré vectoriel
        {
            return m_x * m_x + m_y * m_y;
        }
        float distance(const Vector2D &p)//retourne la distance vectoriel entre deux points (x et y)
        {
            return sqrt((m_x - p.m_x) * (m_x - p.m_x) + (m_y - p.m_y) * (m_y - p.m_y));
        }
        float distanceSquared(const Vector2D &p)//retourne la distance au carré vectoriel entre deux points (x et y)
        {
            return (m_x - p.m_x) * (m_x - p.m_x) + (m_y - p.m_y) * (m_y - p.m_y);
        }
        float dot(const Vector2D &p)
        {
            return m_x * p.m_x + m_y * p.m_y;
        }
        float cross(const Vector2D &p)
        {
            return m_x * p.m_y - m_y * p.m_x;
        }
        Vector2D& ortho()
        {
            setVector2D(-m_y, m_x);
            return *this;
        }
        float normal(float desiredNorm = 1.f)
        {
            float len = length();
            if(len > EPSILON){
                float mult = desiredNorm/len; 
                m_x *= mult; m_y *= mult;
                return len;
            }
            m_x = m_y = 0.f;
            return 0.f;
        }
        Vector2D& normalize()
        {
            if(length() != 0){
                float len = length();
                m_x /= len;
                m_y /= len;
                return *this;
            }
            m_x = m_y = 0;
            return *this;
        }
        Vector2D& setAdd(Vector2D& p)
        {
            m_x = m_x + p.x();
            m_y = m_y + p.y();
            return *this;
        }
        Vector2D& setSub(Vector2D& p)
        {
            m_x = m_x - p.m_x;
            m_y = m_y - p.m_y;
            return *this;
        }
        //multiplie par un scalaire(un nombre réel)
        Vector2D& scaleBy(float nb = 1.f)
        {
            m_x *= nb;
            m_y *= nb;
            return *this;
        }
        //permet de trouve le point le plus proche sur une droite depuis un point
        Vector2D* closest(Vector2D a, Vector2D b) {
            float da = b.m_y - a.m_y;
            float db = a.m_x - b.m_x;
            float c1 = da*a.m_x + db*a.m_y;
            float c2 = -db*m_x + da*m_y;
            float det = da*da + db*db;
            float cx = 0;
            float cy = 0;
        
            if (det != 0) {
                cx = (da*c1 - db*c2) / det;
                cy = (da*c2 + db*c1) / det;
            } else {
                // Le point est déjà sur la droite
                cx = m_x;
                cy = m_y;
            }
        
            return new Vector2D(cx, cy);
        }
};

class Unit : public Vector2D
{
    protected:
        int id;
        Vector2D m_coords;
        Vector2D m_vitesse;
        float r;
    public:
        Unit(){}
        ~Unit(){}
};

class Target : public Vector2D
{
    protected:
        float r;
    public:
        Target(float x = 0.0, float y = 0.0)
        {
            Vector2D(x, y);
            r = 600.00;
        }
        ~Target(){}
};

class Pod : public Vector2D
{
    protected:
        Vector2D m_coords;
        Vector2D m_lastCoords;
        float m_angle;
    public:
        Pod()
        {
            //coords instant
            m_coords.setVector2D(0.0, 0.0);        
            //coords last position
            m_lastCoords.setVector2D(0.0, 0.0);            
            m_angle = 0.0;
        }
        ~Pod(){}
        void setPod(float x = 0.0, float y = 0.0)
        {
            m_coords.setVector2D(x, y);          
        }
};

class MyPod : public Pod
{
    protected:
        Vector2D m_coordsTarget;
        Vector2D m_lastTarget;
        Vector2D m_speedInstant;
        
        float m_nextCheckPointDist;
        float m_nextCheckPointAngle;
        float m_dist;
        int m_thrust;
        bool m_boost;
    public:
        MyPod() : Pod()
        {            
            //coords target
            m_coordsTarget.setVector2D(0.0, 0.0);
            //different speed
            m_speedInstant.setVector2D(0.0, 0.0); //instant speed on X and Y
            
            m_nextCheckPointDist = 0.0;
            m_nextCheckPointAngle = 0.0;
            m_thrust = 100;
            m_boost = true;
        }
        ~MyPod(){}
        void setPod(float x = 0.0, float y = 0.0, float targetX = 0.0, float targetY = 0.0, float nextCheckPointD = 0.0, float nextCheckPointAngle = 0.0)
        {            
            Pod::setPod(x, y);
            m_coordsTarget.setVector2D(targetX, targetY);                
            m_nextCheckPointDist = nextCheckPointD;
            m_nextCheckPointAngle = nextCheckPointAngle;
            m_thrust = 100;
            purchase();
            seek();
            //output();
        }
        void setThrust()
        { 
            if(m_nextCheckPointAngle >= 130 || m_nextCheckPointAngle <= -130){
                m_thrust = 0;
            }else if(m_nextCheckPointAngle >= 90 || m_nextCheckPointAngle <= -90){
                m_thrust = 50;
            }else{
                if(m_dist <= 3000 && m_nextCheckPointDist <= 2300)
                    m_thrust = 75;
                else if(m_dist > 3000 && m_dist < 6000  && m_nextCheckPointDist <= 2300)
                    m_thrust = 40;
                else if(m_dist >= 6000  && m_nextCheckPointDist <= 2300)
                    m_thrust = 70;
                else
                    m_thrust = 100;
            }   
        }
        void checkAngle()
        {
            if(m_nextCheckPointAngle >= 180 || m_nextCheckPointAngle <= -180){
                m_thrust = 0;
            }else if(m_nextCheckPointAngle >= 90 || m_nextCheckPointAngle <= -90){
                m_thrust /= 2;
            }else if(m_nextCheckPointAngle >= 45 || m_nextCheckPointAngle <= -45){ 
                m_thrust = (m_thrust / m_nextCheckPointAngle)*10;
            }
        }
        void checkDistance()
        {
            if(m_dist <= 3000 && m_nextCheckPointDist <= 2300)
                m_thrust = 80, checkAngle();
            else if(m_dist > 3000 && m_dist < 6000  && m_nextCheckPointDist <= 2300)
                m_thrust = 40, checkAngle();
            else if(m_dist >= 6000  && m_nextCheckPointDist <= 2300)
                m_thrust = 75, checkAngle();
            else
                m_thrust = 100;
        }
        void purchase()
        {
            calculSpeed();
            setThrust();
            cerr << "X et Y : " << m_coords.x() << " " << m_coords.y() <<  endl;
            cerr << "Thrust : " << m_thrust<< endl;
            cerr << "Tx : " << m_coordsTarget.x() << ", Ty : " << m_coordsTarget.y() << endl;
            cerr << "Angle : " << m_nextCheckPointAngle << endl;
            cerr << "Distance : " << m_nextCheckPointDist << endl;
            cerr << "Distance calculé : " << m_dist << endl;
                        
        }
        void seek()
        {            
            float m_speed = m_speedInstant.normal(), MAX_FORCE = (m_thrust / 100) +2.0;
            Vector2D steering, desired = m_coordsTarget, velocity(-m_speedInstant.x(), -m_speedInstant.y()), position;
            desired.setSub(m_coords);            
            desired.normal(m_speed);
            steering = desired.setSub(velocity);
            steering.normal(MAX_FORCE);            
            velocity = desired.setAdd(steering);
            velocity.normal(m_speed);
            desired.setAdd(velocity);
            m_coords.setAdd(desired);  
            
        }
        void calculSpeed()
        {            
            if(m_coords.x() != m_lastCoords.x() || m_coords.y() != m_lastCoords.y())
            {
                m_speedInstant.setX((m_coords.x() - m_lastCoords.x()) / 2);
                m_speedInstant.setY((m_coords.y() - m_lastCoords.y()) / 2); 
                m_lastCoords.setX(m_coords.x()*0.85);
                m_lastCoords.setY(m_coords.y()*0.85);
            }
            
            //ne va pas !!!
            if(m_coordsTarget.x() != m_lastTarget.x() || m_coordsTarget.y() != m_lastTarget.y())
            {
                m_dist = m_lastTarget.distance(m_coordsTarget);
                m_angle = m_nextCheckPointAngle;
            }
            else
            {
                m_lastTarget = m_coordsTarget;
            }
            
        }
        void goBoost(int x, int y)
        {
            if(m_nextCheckPointDist >= 6500 && m_boost)
            {
                if(m_nextCheckPointAngle <= 10 && m_nextCheckPointAngle >= -10)
                {
                    cout << (int)m_coords.x() << " " << (int)m_coords.y() << " " << "BOOST" << endl;
                    m_boost = false;
                }
            }
            
        }
        void output(int x, int y)
        {
            if(m_boost)
                goBoost(x,y);
            cout << (int)m_coords.x() << " " << (int)m_coords.y() << " " << m_thrust << endl;
        }
};



int main()
{
    MyPod * maboul = new MyPod();
    int Lap = 0;
    // game loop
    while (1) {
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        maboul->setPod(x, y, nextCheckpointX, nextCheckpointY, nextCheckpointDist, nextCheckpointAngle);
        
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();
        //cerr << "opponentX : " << opponentX << " , opponentY : " << opponentY << endl;        
        maboul->output(opponentX, opponentY);
    }
}