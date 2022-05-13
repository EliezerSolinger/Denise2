#ifndef DMATH_HPP
#define DMATH_HPP

#include <math.h> /* sqrt() */

namespace DMath {

    const float PI = 3.14159265358979323846;
    const float HALF_PI = 1.57079632679489661923;
    const float TWO_PI = 6.28318530717958647692;
    const float DEG_TO_RAD = 0.017453292519943295769236907684886;
    const float RAD_TO_DEG = 57.295779513082320876798154814105;
    const float EULER = 2.718281828459045235360287471352;

    static inline float degtorad(float deg) { return deg * DEG_TO_RAD;}
    static inline float radtodeg(float rad) { return rad * RAD_TO_DEG;}   
    static inline float square(float x) { return x * x; }
    static inline float clamp(float x, float min, float max) { return x < min ? min : (x > max ? max : x); }
    static inline float fast_lerp(float a,float b,float t) { return a + (b - a) * t; }
    static inline float lerp(float a,float b,float t) { return ((1.0f-t)*a+(t*b)); }
    static inline float abs(float x) { return x < 0 ? -x : x; }
    static inline float float_equals(float a, float b) { return abs(a - b) < 1e-6; }
    static inline float min(float a, float b) { return a < b ? a : b; }
    static inline float max(float a, float b) { return a > b ? a : b; }
    static inline float sign(float x) { return x < 0 ? -1 : 1; }

    /** EXPERIMENTAL THIS MAY NOT WORK PROPERLY*/
    static inline float cos_from_sin(float sin, float angle) { 
        float cos=sqrt(1-sin*sin);
        float a=angle+HALF_PI;
        float b = a - ((int)(a / TWO_PI) * TWO_PI);
        if (b < 0) b += TWO_PI;
        return (b >= PI) ? -cos : cos;
     }

    class Vec3 {
        public:
        float x, y, z;
        Vec3() { x = y = z = 0; }
        Vec3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
        
        /* overload operators */
        Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
        Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
        Vec3 operator*(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
        Vec3 operator/(const Vec3& v) const { return Vec3(x / v.x, y / v.y, z / v.z); }
        Vec3 operator+=(Vec3 v) {
            this->x += v.x; this->y += v.y; this->z += v.z;
             return *this;
        }
        Vec3 operator-=(Vec3 v) {
            this->x -= v.x; this->y -= v.y; this->z -= v.z;
             return *this;
        }
        Vec3 operator+(float s) const { return Vec3(x + s, y + s, z + s); }
        Vec3 operator-(float s) const { return Vec3(x - s, y - s, z - s); }
        Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
        Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }
        Vec3 operator-() const { return Vec3(-x, -y, -z); }
        Vec3 operator+=(float s)  {
            this->x += s; this->y += s; this->z += s;
             return *this;
        }
        Vec3 operator-=(float s)  {
            this->x -= s; this->y -= s; this->z -= s;
             return *this;
        }
        

        inline Vec3 inverse() const { return Vec3(-x, -y, -z); }
        inline float dot() const { return x * x + y * y + z * z; }
        inline float dot(Vec3 v) const { return x * v.x + y * v.y + z * v.z; }
        inline float length() const { return sqrt(dot()); }
        inline float magnitude() const { return length(); }
        inline Vec3 normalize() const { return *this / magnitude(); }
        inline Vec3 cross(Vec3 v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
        
        static inline Vec3 ZERO() { return Vec3(0, 0, 0); }
        static inline Vec3 UNIT() { return Vec3(1, 1, 1); }
        static inline Vec3 X() { return Vec3(1, 0, 0); }
        static inline Vec3 Y() { return Vec3(0, 1, 0); }
        static inline Vec3 Z() { return Vec3(0, 0, 1); }
        static inline Vec3 UP() { return Vec3(0, 1, 0); }
        static inline Vec3 DOWN() { return Vec3(0, -1, 0); }
        static inline Vec3 LEFT() { return Vec3(-1, 0, 0); }
        static inline Vec3 RIGHT() { return Vec3(1, 0, 0); }
        static inline Vec3 FORWARD() { return Vec3(0, 0, 1); }
        static inline Vec3 BACK() { return Vec3(0, 0, -1); }
    };


    class Vec2 {
        public: float x, y;
        public: Vec2() { x = y = 0; }
        public: Vec2(float x, float y) { this->x = x; this->y = y; }

        /* overload operators */
        Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
        Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
        Vec2 operator*(const Vec2& v) const { return Vec2(x * v.x, y * v.y); }
        Vec2 operator/(const Vec2& v) const { return Vec2(x / v.x, y / v.y); }
        Vec2 operator+(float s) const { return Vec2(x + s, y + s); }
        Vec2 operator-(float s) const { return Vec2(x - s, y - s); }
        Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
        Vec2 operator/(float s) const { return Vec2(x / s, y / s); }

        inline Vec2 inverse() const { return Vec2(-x, -y); }
        inline float dot() const { return x * x + y * y; }
        inline float length() const { return sqrt(dot()); }
        inline float magnitude() const { return length(); }
        inline Vec2 normalize() const { return *this / magnitude(); }

        static inline Vec2 ZERO() { return Vec2(0, 0); }
        static inline Vec2 UNIT() { return Vec2(1, 1); }
        static inline Vec2 X() { return Vec2(1, 0); }
        static inline Vec2 Y() { return Vec2(0, 1); }
        static inline Vec2 UP() { return Vec2(0, 1); }
        static inline Vec2 DOWN() { return Vec2(0, -1); }
        static inline Vec2 LEFT() { return Vec2(-1, 0); }
        static inline Vec2 RIGHT() { return Vec2(1, 0); }
        
    };

    class Color {
        public: float r,g,b,a;
        Color() { r = g = b = a = 1; }
        Color(float red, float green, float blue, float alpha) { r = red; g = green; b = blue; a = alpha; }
        static inline Color WHITE() { return Color(1,1,1,1); }
        static inline Color BLACK() { return Color(0,0,0,1); }
        static inline Color RED() { return Color(1,0,0,1); }
        static inline Color GREEN() { return Color(0,1,0,1); }
        static inline Color BLUE() { return Color(0,0,1,1); }
        static inline Color YELLOW() { return Color(1,1,0,1); }
        static inline Color CYAN() { return Color(0,1,1,1); }
        static inline Color MAGENTA() { return Color(1,0,1,1); }
        static inline Color GRAY() { return Color(0.5,0.5,0.5,1); }
        static inline Color LIGHT_GRAY() { return Color(0.75,0.75,0.75,1); }
        static inline Color DARK_GRAY() { return Color(0.25,0.25,0.25,1); }
        static inline Color ORANGE() { return Color(1,0.5,0,1); }
        static inline Color PURPLE() { return Color(0.5,0,0.5,1); }
        static inline Color PINK() { return Color(1,0.75,0.75,1); }
        static inline Color BROWN() { return Color(0.5,0.25,0,1); }
        static inline Color LIME() { return Color(0,1,0,1); }
    };
    class Mat4 {
        public: float m[4][4];
        Mat4() {
            m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
            m[0][1] = m[0][2] = m[0][3] = 0;
            m[1][0] = m[1][2] = m[1][3] = 0;
            m[2][0] = m[2][1] = m[2][3] = 0;
            m[3][0] = m[3][1] = m[3][2] = 0;
        }
        Mat4(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33) {
            m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
            m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
            m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
            m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
        }
        static inline Mat4 IDENTITY() {
            return Mat4(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
        }
        static inline Mat4 ZERO() {
            return Mat4(0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0,
                        0, 0, 0, 0);
        }
        
        static inline Mat4 mul(Mat4 m1, Mat4 m2) {
            return Mat4(
                m2.m[0][0] * m1.m[0][0] + m2.m[0][1] * m1.m[1][0] + m2.m[0][2] * m1.m[2][0] + m2.m[0][3] * m1.m[3][0] , 
                m2.m[0][0] * m1.m[0][1] + m2.m[0][1] * m1.m[1][1] + m2.m[0][2] * m1.m[2][1] + m2.m[0][3] * m1.m[3][1] , 
                m2.m[0][0] * m1.m[0][2] + m2.m[0][1] * m1.m[1][2] + m2.m[0][2] * m1.m[2][2] + m2.m[0][3] * m1.m[3][2] , 
                m2.m[0][0] * m1.m[0][3] + m2.m[0][1] * m1.m[1][3] + m2.m[0][2] * m1.m[2][3] + m2.m[0][3] * m1.m[3][3] ,
                
                m2.m[1][0] * m1.m[0][0] + m2.m[1][1] * m1.m[1][0] + m2.m[1][2] * m1.m[2][0] + m2.m[1][3] * m1.m[3][0] , 
                m2.m[1][0] * m1.m[0][1] + m2.m[1][1] * m1.m[1][1] + m2.m[1][2] * m1.m[2][1] + m2.m[1][3] * m1.m[3][1] , 
                m2.m[1][0] * m1.m[0][2] + m2.m[1][1] * m1.m[1][2] + m2.m[1][2] * m1.m[2][2] + m2.m[1][3] * m1.m[3][2] , 
                m2.m[1][0] * m1.m[0][3] + m2.m[1][1] * m1.m[1][3] + m2.m[1][2] * m1.m[2][3] + m2.m[1][3] * m1.m[3][3] ,
               
                m2.m[2][0] * m1.m[0][0] + m2.m[2][1] * m1.m[1][0] + m2.m[2][2] * m1.m[2][0] + m2.m[2][3] * m1.m[3][0],
                m2.m[2][0] * m1.m[0][1] + m2.m[2][1] * m1.m[1][1] + m2.m[2][2] * m1.m[2][1] + m2.m[2][3] * m1.m[3][1] , 
                m2.m[2][0] * m1.m[0][2] + m2.m[2][1] * m1.m[1][2] + m2.m[2][2] * m1.m[2][2] + m2.m[2][3] * m1.m[3][2] , 
                m2.m[2][0] * m1.m[0][3] + m2.m[2][1] * m1.m[1][3] + m2.m[2][2] * m1.m[2][3] + m2.m[2][3] * m1.m[3][3],
                
                m2.m[3][0] * m1.m[0][0] + m2.m[3][1] * m1.m[1][0] + m2.m[3][2] * m1.m[2][0] + m2.m[3][3] * m1.m[3][0], 
                m2.m[3][0] * m1.m[0][1] + m2.m[3][1] * m1.m[1][1] + m2.m[3][2] * m1.m[2][1] + m2.m[3][3] * m1.m[3][1] , 
                m2.m[3][0] * m1.m[0][2] + m2.m[3][1] * m1.m[1][2] + m2.m[3][2] * m1.m[2][2] + m2.m[3][3] * m1.m[3][2] , 
                m2.m[3][0] * m1.m[0][3] + m2.m[3][1] * m1.m[1][3] + m2.m[3][2] * m1.m[2][3] + m2.m[3][3] * m1.m[3][3] 
            );
        }
        static inline Mat4 rotation(Vec3 angle) {
            Mat4 mat=Mat4::IDENTITY();
            float sinX = sinf(angle.x);
            float cosX = cos_from_sin(sinX,angle.x);
            float sinY =  sinf(angle.y);
            float cosY =  cos_from_sin(sinY,angle.y);
            float sinZ =  sinf(angle.z);
            float cosZ =  cos_from_sin(sinZ,angle.z);
            float m_sinX = -sinX;
            float m_sinY = -sinY;
            float m_sinZ = -sinZ;

            // rotateX
            float nm11 = cosX;
            float nm12 = sinX;
            float nm21 = m_sinX;
            float nm22 = cosX;
            // rotateY
            float nm00 = cosY;
            float nm01 = nm21 * m_sinY;
            float nm02 = nm22 * m_sinY;
            mat.m[0][2] = sinY;
            mat.m[1][2] = (nm21 * cosY);
            mat.m[2][2] = (nm22 * cosY);
            // rotateZ
            mat.m[0][0] = (nm00 * cosZ);
            mat.m[1][0] = (nm01 * cosZ + nm11 * sinZ);
            mat.m[2][0] = (nm02 * cosZ + nm12 * sinZ);
            mat.m[0][1] = (nm00 * m_sinZ);
            mat.m[1][1] = (nm01 * m_sinZ + nm11 * cosZ);
            mat.m[2][1] = (nm02 * m_sinZ + nm12 * cosZ);
            return mat;
        }
        static inline Mat4 rotation_old(Vec3 angle) {
            Vec3 s=Vec3(sin(angle.x), sin(angle.y), sin(angle.z)); // sin(angle)
            Vec3 c=Vec3(cos(angle.x), cos(angle.y), cos(angle.z)); // cos(angle)

            Mat4 n =Mat4(
                c.y,-s.x*-s.y, c.x*-s.y, 0,  
                1,c.x,s.x,0,
                0,-s.x,c.x,0,
                0,0,0,1
            );
            return Mat4(
                n.m[0][0] * c.z, n.m[0][0] * -s.z, s.y, 0,
                n.m[0][1] * c.z + n.m[1][1] * s.z, (n.m[0][1] * -s.z + n.m[1][1] * c.z),(n.m[2][1] * c.y),0,
                n.m[0][2] * c.z + n.m[1][2] * s.z, (n.m[0][2] * -s.z + n.m[1][2] * c.z),(n.m[2][2] * c.y),0,
                0, 0, 0, 1
            );
        }
        /** EXPERIMENTAL */
        static inline Mat4 __rotation(Vec3 angle) {
            Vec3 s=Vec3(sin(angle.x), sin(angle.y), sin(angle.z)); // sin(angle)
            Vec3 c=Vec3(cos(angle.x), cos(angle.y), cos(angle.z)); // cos(angle)
            
            return Mat4(
                c.x * c.y, c.x * s.y * s.z - s.x * c.z, c.x * s.y * c.z + s.x * s.z, 0,
                s.x * c.y, s.x * s.y * s.z + c.x * c.z, s.x * s.y * c.z - c.x * s.z, 0,
                -s.y, c.y * s.z, c.y * c.z, 0,
                0, 0, 0, 1
            );
        }        
        static inline Mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
            float tanHalfFovy = (float) tan(fovy / (float) 2);

            Mat4 result = Mat4::ZERO();
            result.m[0][0] = (float) 1 / (aspect * tanHalfFovy);
            result.m[1][1] = (float) 1 / (tanHalfFovy);
            result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
            result.m[2][3] = -(float) 1;
            result.m[3][2] = -((float) 2 * zFar * zNear) / (zFar - zNear);
            return result;
        }
        static inline Mat4 perspective_old(float fovy, float aspect, float zNear, float zFar) {
            float f = 1.0 / tan(fovy / 2.0);
            float range = zNear - zFar;
            return Mat4(
                f / aspect, 0, 0, 0,
                0, f, 0, 0,
                0, 0, (zNear + zFar) / range, 2 * zFar * zNear / range,
                0, 0, -1, 0
            );
        }
        static inline Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
            Mat4 result = Mat4::IDENTITY();
            result.m[0][0] = (float) 2 / (right - left);
            result.m[1][1] = (float) 2 / (top - bottom);
            result.m[2][2] = -(float) 2 / (zFar - zNear);
            result.m[3][0] = -(right + left) / (right - left);
            result.m[3][1] = -(top + bottom) / (top - bottom);
            result.m[3][2] = -(zFar + zNear) / (zFar - zNear);

            return result;
        }
        static inline Mat4 ortho_old(float left, float right, float bottom, float top, float zNear, float zFar) {
            float width = right - left;
            float height = top - bottom;
            float depth = zFar - zNear;
            return Mat4( 
                2 / width, 0, 0, -(right + left) / width,
                0, 2 / height, 0, -(top + bottom) / height,
                0, 0, -2 / depth, -(zFar + zNear) / depth,
                0, 0, 0, 1
            );
        }
        static inline Mat4 lookAt(Vec3 eye, Vec3 center, Vec3 up) {
            Vec3 f = (center - eye).normalize();
            Vec3 s = f.cross(up).normalize();
            Vec3 u = s.cross(f);
            return Mat4(
                s.x, u.x, -f.x, 0,
                s.y, u.y, -f.y, 0,
                s.z, u.z, -f.z, 0,
                -s.dot(eye), -u.dot(eye), f.dot(eye), 1
            );
        }
        /** not tested  */
        inline Mat4 transpose() const {
            return Mat4(
                m[0][0], m[1][0], m[2][0], m[3][0],
                m[0][1], m[1][1], m[2][1], m[3][1],
                m[0][2], m[1][2], m[2][2], m[3][2],
                m[0][3], m[1][3], m[2][3], m[3][3]
            );
        }
        
         inline Mat4 translated(float x,float y, float z) const {
            return Mat4(
                m[0][0], m[0][1], m[0][2], m[0][3],
                m[1][0], m[1][1], m[1][2], m[1][3],
                m[2][0], m[2][1], m[2][2], m[2][3],
                m[3][0] + x, m[3][1] + y, m[3][2] + z, m[3][3]
            );
        } 
        inline Mat4 translated(Vec3 v) const {return translated(v.x, v.y, v.z);}
        inline Mat4 scaled(float x, float y, float z) const {
            return Mat4(
                m[0][0] * x, m[0][1] , m[0][2] , m[0][3],
                m[1][0] , m[1][1] * y, m[1][2] , m[1][3],
                m[2][0] , m[2][1] , m[2][2] * z, m[2][3],
                m[3][0], m[3][1], m[3][2], m[3][3]
            );
        }
        inline Mat4 scaled(Vec3 v) const {return scaled(v.x, v.y, v.z);}
        inline Mat4 scaled(float s) const {return scaled(s, s, s);}
        inline Mat4 rotated(Vec3 v) const {return mul(rotation(v),*this);}
        inline Mat4 rotated(float x,float y,float z) const {return rotated(Vec3(x,y,z));}
        inline Mat4 rotated(float s) const {return rotated(0,0,s);}
        inline Vec3 translation() const {return Vec3(m[3][0], m[3][1], m[3][2]);}
        inline Vec2 translation2D() const {return Vec2(m[3][0], m[3][1]);}
        
        /*inline Mat4 mul(const Mat4& m) const {
            return mul(*this, m);
        }*/
    };

    class Transform {
        public: Vec3 pos,size,angles;
        Transform() {
            pos=Vec3(0,0,0);
            size=Vec3(1,1,1);
            angles=Vec3(0,0,0);
        }
        inline Mat4 matrix() {
            return Mat4().scaled(size).rotated(angles).translated(-pos.x,-pos.y,pos.z);
        }
        inline Mat4 view_matrix() {
            return Mat4().translated(pos);//.rotated(angles).scaled(size);
        }
    };
    class Rect {
        public:
        Vec2 position,size;
        Rect() {
            position=Vec2(0,0);
            size=Vec2(1,1);
        }
    };

}

#endif