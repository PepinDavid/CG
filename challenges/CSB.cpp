#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

#define PI 3.14159265
#define EPSILON 0.00000001
//class Vector2D
//sert à init points coords des Pod et des checkpoints
//et pour les calcules de vecteurs
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
        void setX(float x)
        {
            m_x = x;
        }
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

class Pod : public Vector2D
{
    protected:
        //nos coordonnées
        Vector2D m_coords;
        //nos anciens coordonnées
        Vector2D m_lastCoords;
    public:
        Pod()
        {
            m_coords.setVector2D(0.0, 0.0);        
            m_lastCoords.setVector2D(0.0, 0.0);     
            
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
        //coordonées de la cible
        Vector2D m_coordsTarget;
        //sert a checké si on est passé par un checkpoint
        Vector2D m_actualTarget;
        Vector2D m_lastTarget;
        Vector2D m_speedInstant;
        vector<Vector2D> m_targetsCoords;
        //angle vers la cible
        float m_angle;
        /*
            distance vers la cible 
            un calcul est fait
            dist == m_nextCheckPointDist
        */
        float m_dist;
        //timeout game
        int m_timeout;
        //nombre de tours
        int m_lap = 0;
        //distance vers la cible données en entrée
        float m_nextCheckPointDist;
        //angle vers la cible données en entrée
        float m_nextCheckPointAngle;
        
        int m_thrust;
        bool m_boost;
    public:
        MyPod() : Pod() //appelle du constructeur Pod
        {         
            m_coordsTarget.setVector2D(0.0, 0.0);
            m_speedInstant.setVector2D(0.0, 0.0);
            m_actualTarget.setVector2D(0.0, 0.0);            
            m_nextCheckPointDist = 0.0;
            m_nextCheckPointAngle = 0.0;
            m_thrust = 100;
            m_boost = true;
        }
        ~MyPod(){}
        //init Pod avec les entrées
        void setPod(float x = 0.0, float y = 0.0, float targetX = 0.0, float targetY = 0.0, float nextCheckPointD = 0.0, float nextCheckPointAngle = 0.0)
        {            
            Pod::setPod(x, y);            
            m_coordsTarget.setVector2D(targetX, targetY);
            m_nextCheckPointDist = nextCheckPointD;
            m_nextCheckPointAngle = nextCheckPointAngle;
            m_angle = nextCheckPointAngle;
            m_thrust = 100;
            checkTargets();
            purchase();
            seek();
        }
        //donne la sortie et des infos
        void output(int x, int y)
        {
            cerr << "timeout " << m_timeout << endl;
            cerr << "lap : " << m_lap << endl;
            cerr << "X et Y : " << m_coords.x() << " " << m_coords.y() <<  endl;
            cerr << "Thrust : " << m_thrust<< endl;
            cerr << "Tx : " << m_coordsTarget.x() << ", Ty : " << m_coordsTarget.y() << endl;
            cerr << "Angle calculé : " << m_angle << endl;
            cerr << "Distance calculé : " << m_dist << endl;
            if(m_thrust < 30 && m_thrust > -30)
                m_thrust = 30;
                
            if(m_boost)
                goBoost(x,y);
                
            cout << (int)m_coords.x() << " " << (int)m_coords.y() << " " << abs(m_thrust) << endl;
            
        }
    private:
        //check l'angle vers la cible et met la poussé
        void checkAngle()
        {
            if(m_angle >= 130 || m_angle <= -130){
                    m_thrust = 30;
            }else if(m_angle >= 90 || m_angle <= -90){
                m_thrust = (m_thrust / m_angle)*15;
            }else if(m_angle >= 5 || m_angle <= -5){
                m_thrust = 90;
            }else if(m_angle < 5 || m_angle > -5){
                m_thrust = 100;
            }
        }
        //check la distance vers la cible et met la poussé
        void checkDistance()
        {            
            if(m_nextCheckPointDist > 2300)
                m_thrust = 100, checkAngle();
            else if(m_nextCheckPointDist <= 2300 && m_nextCheckPointDist > 1400)
                m_thrust = 75, checkAngle();
            else
                m_thrust = 45, checkAngle();
        }
        //calcul des données
        void purchase()
        {
            calculSpeed();
            calculDist();
            checkDistance();   
            changeTarget();
            nextTarget();
            
        }
        //recherche de la trajectoire
        void seek()
        {            
            float m_speed = m_speedInstant.normal(),//normalisation du vecteur vitesse
            MAX_FORCE = (m_thrust / 100) + 2.0;//calcule de la force centrifuge
            Vector2D steering,//direction
            desired = m_coordsTarget,//direction desirée
            velocity(-m_speedInstant.x(), -m_speedInstant.y());//velocité de la vitesse instannée
            desired.setSub(m_coords);//on soustrait notre position à la position desirée
            desired.normal(m_speed);//normalisation de la vitesse desirée par rapport a la vitesse instannée
            steering = desired.setSub(velocity); //calcule de la direction désirée
            steering.normal(MAX_FORCE);//normalisation du vecteur par rapport a la force centrigue
            velocity = desired.setAdd(steering); //on ajoute a la direction désirée
            velocity.normal(m_speed);//on normalise par rapport a la vitesse instannée
            desired.setAdd(velocity);//on ajout la velocité a la direction désiré
            m_coords.setAdd(desired);//on change nos coordonnées avec la nouvelle trajectoire
        }
        //calcul de la vitesse instannée
        void calculSpeed()
        {       
            //coeff friction
            float friction = 0.85;
            //tours entre coords actuelle et les anciennes 
            int rd = 2;
            if(m_coords.x() != m_lastCoords.x() || m_coords.y() != m_lastCoords.y())
            {
                m_speedInstant.setVector2D((m_coords.x() - m_lastCoords.x()) / rd, (m_coords.y() - m_lastCoords.y()) / rd);
                m_lastCoords.setVector2D(m_coords.x() * friction, m_coords.y() * friction);
            }                                    
        }
        //calcul de la distance entre le Pod et la cible
        void calculDist(){
            if(m_coordsTarget.x() != m_lastTarget.x() || m_coordsTarget.y() != m_lastTarget.y())
                m_dist = m_coords.distance(m_coordsTarget);
            else         
                m_lastTarget = m_coordsTarget;
        }
        //sert a visé le prochain checkpoint si on est assez près de celui
        void nextTarget(){
            int index = 0;
            //si il y a des checkpoints dans le tableau
            if(m_targetsCoords.size() > 0){
                for(int i = 0; i < m_targetsCoords.size(); i++){
                    //si les coordonnées du checkpoints correspondent a celles visées
                    //on sélectionne le prochain
                    if(m_targetsCoords[i].x() == m_coordsTarget.x() 
                        && m_targetsCoords[i].y() == m_coordsTarget.y())
                            index = i+1;
                }
            }
            //ajout de 2 tours a lap vu que l'on commence a zéro
            if(m_targetsCoords[index].x() > 0 && m_targetsCoords[0].x() == m_coordsTarget.x())
                m_lap = 2; 
            //if on a déjà procédé a un tour et que l'on est proche du checkpoint visé
            //1450 est choisi comme valeur d'approche avec un checkpoint correspond a 600 et le Pod fait 400
            //avec la vitesse du pod lors de l'approche on ajoute 450
            if(m_lap && m_nextCheckPointDist <= 1450){
                if(index >= m_targetsCoords.size())
                    index = 0;
                //si on est pas en timeout on vise le prochain prochain checkpoint
                // et on calcul le futur angle d'approche pour ralentir
                if(m_timeout >= 65){
                    m_coordsTarget.setVector2D(m_targetsCoords[index].x(), m_targetsCoords[index].y());
                    rotate(m_targetsCoords[index]);
                }
            }  
        }
        //ajout des checkpoints dans un tableau
        void checkTargets(){
            if(!m_lap){
                if(m_targetsCoords.size() < 1)
                    m_targetsCoords.push_back(m_coordsTarget);
                else{
                    bool existCoord = false;
                    for(auto &p : m_targetsCoords){
                        if(p.x() == m_coordsTarget.x())
                            existCoord = true;
                    }
                    if(!existCoord)
                        m_targetsCoords.push_back(m_coordsTarget);
                }
            }
        }
        //check si on a passé un checkpoint et réinit du timeout
        void changeTarget(){
            if(m_actualTarget.x() == 0 && m_actualTarget.y() == 0)
                m_actualTarget.setVector2D(m_coordsTarget.x(), m_coordsTarget.y());

            if(m_actualTarget.x() == m_coordsTarget.x())
                m_timeout--;
            else{
                m_timeout = 100;
                m_actualTarget.setVector2D(m_coordsTarget.x(), m_coordsTarget.y());
                setLap();
            }
        }
        //check des tours du circuit
        void setLap(){
            if(m_lap)
                if(m_targetsCoords[m_targetsCoords.size()-1].x() == m_coordsTarget.x())
                    m_lap++;
        }
        float getAngle(Vector2D p) {
            float d = m_coords.distance(p);
            float dx = 0;
            float dy = 0;
            cerr << d << endl;
            if(p.x() > m_x)
                dx = (p.x() - m_x) / d;
            else
                dx = (m_x - p.x()) / d;
            
            if(p.y() > m_y)
                dy = (p.y() - m_y) / d;
            else
                dy = (m_y - p.y()) / d;
            cerr << dx << endl;
            cerr << dy << endl;
            // Trigonométrie simple. On multiplie par 180.0 / PI pour convertir en degré.
            float a = acos(dx) * 180.0 / PI;
            cerr << a << endl;
            // Si le point qu'on veut est en dessus de nous, il faut décaler l'angle pour qu'il soit correct.
            if (dy < 0) {
                a = 360.0 - a;
            }
            cerr << a << endl;
            return a;
        }
        float diffAngle(Vector2D p) {
            float a = getAngle(p);
            // Pour connaitre le sens le plus proche, il suffit de regarder dans les 2 sens et on garde le plus petit
            float right = m_angle <= a ? a - m_angle : 360.0 - m_angle + a;
            float left = m_angle >= a ? m_angle - a : m_angle + 360.0 - a;
        
            if(right < left)
                return right;
            else // On donne un angle négatif s'il faut tourner à gauche
                return -left;
        }
        void rotate(Vector2D p) {
            float a = diffAngle(p);        
            // On ne peut pas tourner de plus de 18° en un seul tour
            if (a > 18.0)
                a = 18.0;
            else if (a < -18.0)
                a = -18.0;  

            m_angle += a;

            // L'opérateur % est lent. Si on peut l'éviter, c'est mieux.
            if (m_angle >= 360.0)
                m_angle = m_angle - 360.0;
            else if (m_angle < 0.0)
                m_angle += 360.0;
        }
        void goBoost(int x, int y)
        {
            Vector2D enemy(x,y);
            if(m_nextCheckPointDist >= 6500 && m_boost && m_lap)
            {
                if(m_angle <= 10 && m_angle >= -10)
                {
                    cout << (int)m_coords.x() << " " << (int)m_coords.y() << " " << "BOOST" << endl;
                    m_boost = false;
                }
            }
            /*else if(m_coords.distance(enemy) < 800 && m_boost && m_lap){
                cout << (int)x << " " << (int)y << " " << "BOOST" << endl;
                    m_boost = false;
            }*/
            
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