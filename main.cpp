// OpenGL includes
#include <GL/glut.h>

// STD includes
#include <iostream>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <ExternalVTKWidget.h>
#include <vtkExternalOpenGLRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkOBJReader.h>

#include <vtkNew.h>

vtkNew<ExternalVTKWidget> externalVTKWidget;
//vtkNew<vtkOBJReader> objReader;

bool initilaized = false;

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
   if (!initilaized)
     {
     vtkNew<vtkPolyDataMapper> mapper;
     vtkNew<vtkActor> actor;
     actor->SetMapper(mapper.GetPointer());
     externalVTKWidget->GetRenderer()->AddActor(actor.GetPointer());
     vtkNew<vtkSphereSource> ss;
     mapper->SetInputConnection(ss->GetOutputPort());
//     mapper->SetInputConnection(objReader->GetOutputPort());
     externalVTKWidget->GetRenderer()->ResetCamera();
     initilaized = true;
     }

   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

   glFlush();  // Render now

   externalVTKWidget->GetRenderWindow()->SetSize(400, 400);
   externalVTKWidget->GetRenderWindow()->Render();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
//   objReader->SetFileName(argv[1]);
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitWindowSize(400,400);   // Set the window's initial width & height
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
