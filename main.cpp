// OpenGL includes
#if defined(__APPLE__)
# include <GLUT/glut.h> // Include OpenGL API.
#else
# include "vtkWindows.h" // Needed to include OpenGL header on Windows.
# include <GL/glut.h> // Include OpenGL API.
#endif

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
#include <vtkCubeSource.h>
#include <vtkOBJReader.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkLight.h>

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
  if (initilaized)
    {
    glutSetWindow(windowId);
    }
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
     vtkRenderer* ren = externalVTKWidget->AddRenderer();
     ren->AddActor(actor.GetPointer());
     renWin->SetSize(400,400);
     vtkNew<vtkCallbackCommand> callback;
     callback->SetCallback(MakeCurrentCallback);
     renWin->AddObserver(vtkCommand::WindowMakeCurrentEvent,
                         callback.GetPointer());
     externalVTKWidget->SetRenderWindow(renWin.GetPointer());
     vtkNew<vtkCubeSource> ss;
     //ss->SetCenter(-0.5,0.5,0.5);
     mapper->SetInputConnection(ss->GetOutputPort());
     ren->ResetCamera();
     //externalVTKWidget->GetRenderer()->PreserveColorBufferOff();
     //externalVTKWidget->GetRenderer()->PreserveDepthBufferOff();
     actor->RotateX(45.0);
     actor->RotateY(45.0);
     initilaized = true;

     vtkNew<vtkLight> light;
     light->SetLightTypeToSceneLight();
     light->SetPosition(0, 0, 1);
     light->SetConeAngle(25.0);
     light->SetPositional(true);
     light->SetFocalPoint(0, 0, 0);
     light->SetDiffuseColor(1, 0, 0);
     light->SetAmbientColor(0, 1, 0);
     light->SetSpecularColor(0, 0, 1);
     externalVTKWidget->GetRenderWindow()->Render();
     // Make sure light is added after first render call
     ren->AddLight(light.GetPointer());
     }

   glEnable(GL_DEPTH_TEST);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

   glFlush();  // Render now
//   glBegin(GL_TRIANGLES);
//     glVertex3f(-0.5,-0.5,0.0);
//     glVertex3f(0.5,-0.5,0.0);
//     glVertex3f(0.5,0.5,0.0);
//   glEnd();

   externalVTKWidget->GetRenderWindow()->Render();

  /* Display the result */
  glutSwapBuffers();
}

void handleResize(int w, int h)
{
  externalVTKWidget->GetRenderWindow()->SetSize(w, h);
  glutPostRedisplay();
}

void onexit(void)
{
  initilaized = false;
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
//   objReader->SetFileName(argv[1]);
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize(400,400);   // Set the window's initial width & height
   glutInitWindowPosition(400, 200); // Position the window's initial top-left corner
   windowId = glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutReshapeFunc(handleResize); // Register resize callback handler for window resize
   atexit(onexit);
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
