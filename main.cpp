#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "Transform.hpp"
#include "CargaText.h"
#include "Face.h"
#include "Vertice.h"
#include <iostream>

using namespace std;

int main( void )
{
    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    
    GLFWwindow* window;
    
   // Object sol = Object();
    Load plane;
    plane.loadObject("plane.obj");

   // Object tierra = Object();
  /*  Load tierra;
	tierra.loadObject("roca.obj");*/

    if( !glfwInit() )
    {
        fprintf( stderr, "Fallo al inicializar GLFW\n" );
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Proyecto Avion Movimiento Circular", NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

//  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

//  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

//  Proyección en perspectiva
//   glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Transform Tr = Transform();
    float p_angle = 0.0f;
	
    do {
        glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2], 
                camera[0], camera[1], camera[2], 
                0.0, 1.0, 0.0);


        // Dibujar el Avion
        arma::fmat trans= Tr.S(0.3, 0.3, 0.3);
		
		p_angle = (p_angle > -360.0f) ? p_angle-5.0 : 0.0f;

        arma::fmat transf= Tr.R(0.0f, 1.0f, 0.0f, p_angle) * Tr.T(-0.7, 0.0, 0.0) * Tr.S(0.5, 0.5, 0.5) * trans;
		
		std::vector< Vertice> p_vertices = plane.v;
		std::vector< Vertice> plane_vertices;

	  for ( unsigned int i=0; i<p_vertices.size(); i++ ) {
            arma::fcolvec v = p_vertices[i].h();
            arma::fcolvec vp = transf * v;
            Vertice rv = Vertice(vp[0],vp[1],vp[2]);
            plane_vertices.push_back(rv);
        }
		
		glColor3f(1.0, 1.0, 0.0);
		
		 for(int i=0;i<plane.f.size();i++) //ciclo de dibujado
        {
		glBegin(GL_TRIANGLES);//comienza la funcion de creacion de caras de 3 lados
			    glNormal3f(plane.vn[plane.f[i].facenum-1].x,plane.vn[plane.f[i].facenum-1].y,plane.vn[plane.f[i].facenum-1].z);
				glVertex3f(plane_vertices[plane.f[i].faces[0]-1].x,plane_vertices[plane.f[i].faces[0]-1].y,plane_vertices[plane.f[i].faces[0]-1].z);
				glVertex3f(plane_vertices[plane.f[i].faces[1]-1].x,plane_vertices[plane.f[i].faces[1]-1].y,plane_vertices[plane.f[i].faces[1]-1].z);
				glVertex3f(plane_vertices[plane.f[i].faces[2]-1].x,plane_vertices[plane.f[i].faces[2]-1].y,plane_vertices[plane.f[i].faces[2]-1].z);
		glEnd();
		}
		
		glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwTerminate();

    return 0;
}