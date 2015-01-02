// OpenGL includes
#include <GL/glut.h>

// STD includes
#include <iostream>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <ExternalVTKWidget.h>
#include <vtkExternalOpenGLRenderer.h>
#include <vtkExternalOpenGLRenderWindow.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkOBJReader.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

#include <vtkNew.h>

vtkNew<ExternalVTKWidget> externalVTKWidget;
vtkNew<vtkExternalOpenGLRenderWindow> renWin;
//vtkNew<vtkOBJReader> objReader;

bool initilaized = false;
static int windowId = -1;

static void MakeCurrentCallback(vtkObject* caller,
                                long unsigned int eventId,
                                void * clientData,
                                void * callData)
{
  glutSetWindow(windowId);
}

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
     renWin->SetSize(400,400);
//     renWin->SetPosition(400,200);
//     vtkNew<vtkCallbackCommand> callback;
//     callback->SetCallback(MakeCurrentCallback);
//     renWin->AddObserver(vtkCommand::WindowMakeCurrentEvent, callback.GetPointer());
     externalVTKWidget->SetRenderWindow(renWin.GetPointer());
     vtkNew<vtkSphereSource> ss;
     ss->SetCenter(-0.5,0.5,0);
     mapper->SetInputConnection(ss->GetOutputPort());
//     mapper->SetInputConnection(objReader->GetOutputPort());
     externalVTKWidget->GetRenderer()->ResetCamera();
     initilaized = true;
     }

   glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

   glFlush();  // Render now
   glBegin(GL_TRIANGLES);
     glVertex3f(-0.5,-0.5,0.0);
     glVertex3f(0.5,-0.5,0.0);
     glVertex3f(0.5,0.5,0.0);
   glEnd();

//  externalVTKWidget->GetRenderWindow()->SetSize(400, 400);
   externalVTKWidget->GetRenderWindow()->Render();

  /* Display the result */
  glutSwapBuffers();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
//   objReader->SetFileName(argv[1]);
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitWindowSize(400,400);   // Set the window's initial width & height
   glutInitWindowPosition(400, 200); // Position the window's initial top-left corner
   windowId = glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
