#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

struct Vertex
{
  GLfloat x,y,z;
};

GLuint vbo = 0;
void init()
{
    std::vector<Vertex> verts;
    Vertex v;
    v.x = 0; v.y = 2; v.z = -4;
    verts.push_back( v );
    v.x = -2; v.y = -2; v.z = -4;
    verts.push_back( v );
    v.x = 2; v.y = -2; v.z = -4;
    verts.push_back( v );

    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData
        (
        GL_ARRAY_BUFFER,
        sizeof( Vertex ) * verts.size(),
        &verts[0],
        GL_STATIC_DRAW
        );
}

void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( -5, 5, -5, 5, -5, 5 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnableClientState( GL_VERTEX_ARRAY );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glVertexPointer( 3, GL_FLOAT, 0, 0 );

    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glDisableClientState( GL_VERTEX_ARRAY );

    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInitWindowSize( 600, 600 );
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutCreateWindow( "GLUT" );
    glewInit();

    glutDisplayFunc( display );
    init();
    glutMainLoop();
    return 0;
}
