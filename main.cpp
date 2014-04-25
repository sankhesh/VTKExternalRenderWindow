// OpenGL includes
#include <GL/glut.h>

// STD includes
#include <iostream>

#include "vtkExtOpenGLRenderWindow.h"
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>

#include <vtkNew.h>

vtkNew<vtkRenderer> ren;
vtkNew<vtkExtOpenGLRenderWindow> renWin;
bool initilaized = false;

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
   if (!initilaized)
     {
       renWin->AddRenderer(ren.GetPointer());
       vtkNew<vtkPolyDataMapper> mapper;
       vtkNew<vtkActor> actor;
       actor->SetMapper(mapper.GetPointer());
        ren->AddActor(actor.GetPointer());
        vtkNew<vtkSphereSource> ss;
        mapper->SetInputConnection(ss->GetOutputPort());
        initilaized = true;
     }
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

   // Draw a    Red 1x1 Square centered at origin

   renWin->Render();
   glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitWindowSize(400, 400);   // Set the window's initial width & height
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title   
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
