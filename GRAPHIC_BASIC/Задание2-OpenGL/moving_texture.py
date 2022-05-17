from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys
from PIL.Image import *

window = 0

# Rotations for cube.
xrot = yrot = zrot = 0.0

def LoadTextures():
    global textures
    image = open("Wall.bmp")

    ix = image.size[0]
    iy = image.size[1]
    image = image.tobytes("raw", "RGBX", 0, -1)

    textures = glGenTextures(3)

    glBindTexture(GL_TEXTURE_2D, int(textures[0]))

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, iy, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)

    glBindTexture(GL_TEXTURE_2D, int(textures[1]))
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, iy, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image)

    glBindTexture(GL_TEXTURE_2D, int(textures[2]))
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST)
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ix, iy,
                      GL_RGBA, GL_UNSIGNED_BYTE, image)


def InitGL(Width, Height):
    global quadratic

    LoadTextures()

    quadratic = gluNewQuadric()
    gluQuadricNormals(quadratic, GLU_SMOOTH)
    gluQuadricTexture(quadratic, GL_TRUE)			

    glEnable(GL_TEXTURE_2D)

    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)					
    glDepthFunc(GL_LESS)				
    glEnable(GL_DEPTH_TEST)				
    glShadeModel(GL_SMOOTH)	

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()				
    gluPerspective(45.0, float(Width)/float(Height), 0.1, 100.0)

    glMatrixMode(GL_MODELVIEW)

    glLightfv(GL_LIGHT0, GL_AMBIENT, (0.5, 0.5, 0.5, 1.0))
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (1.0, 1.0, 1.0, 1.0))
    glLightfv(GL_LIGHT0, GL_POSITION, (0.0, 0.0, 2.0, 1.0))
    glEnable(GL_LIGHT0)

def ReSizeGLScene(Width, Height):
    if Height == 0:
        Height = 1

    glViewport(0, 0, Width, Height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, float(Width)/float(Height), 0.1, 100.0)
    glMatrixMode(GL_MODELVIEW)


def DrawCube():
    glBegin(GL_QUADS)

    glTexCoord2f(0.0, 0.0)
    glVertex3f(-0.5, -0.5,  0.5)
    glTexCoord2f(0.5, 0.0)
    glVertex3f(0.5, -0.5,  0.5)
    glTexCoord2f(0.5, 0.5)
    glVertex3f(0.5,  0.5,  0.5)
    glTexCoord2f(0.0, 0.5)
    glVertex3f(-0.5,  0.5,  0.5)

    # Back Face
    glTexCoord2f(0.5, 0.0)
    glVertex3f(-0.5, -0.5, -0.5)
    glTexCoord2f(0.5, 0.5)
    glVertex3f(-0.5,  0.5, -0.5)
    glTexCoord2f(0.0, 0.5)
    glVertex3f(0.5,  0.5, -0.5)
    glTexCoord2f(0.0, 0.0)
    glVertex3f(0.5, -0.5, -0.5)

    glTexCoord2f(0.0, 0.5)
    glVertex3f(-0.5,  0.5, -0.5)
    glTexCoord2f(0.0, 0.0)
    glVertex3f(-0.5,  0.5,  0.5)
    glTexCoord2f(0.5, 0.0)
    glVertex3f(0.5,  0.5,  0.5)
    glTexCoord2f(0.5, 0.5)
    glVertex3f(0.5,  0.5, -0.5)

    glTexCoord2f(0.5, 0.5)
    glVertex3f(-0.5, -0.5, -0.5)  
    glTexCoord2f(0.0, 0.5)
    glVertex3f(0.5, -0.5, -0.5) 
    glTexCoord2f(0.0, 0.0)
    glVertex3f(0.5, -0.5,  0.5)  
    glTexCoord2f(0.5, 0.0)
    glVertex3f(-0.5, -0.5,  0.5) 

    glTexCoord2f(0.5, 0.0)
    glVertex3f(0.5, -0.5, -0.5) 
    glTexCoord2f(0.5, 0.5)
    glVertex3f(0.5,  0.5, -0.5) 
    glTexCoord2f(0.0, 0.5)
    glVertex3f(0.5,  0.5,  0.5)  
    glTexCoord2f(0.0, 0.0)
    glVertex3f(0.5, -0.5,  0.5)

    glTexCoord2f(0.0, 0.0)
    glVertex3f(-0.5, -0.5, -0.5)
    glTexCoord2f(0.5, 0.0)
    glVertex3f(-0.5, -0.5,  0.5)
    glTexCoord2f(0.5, 0.5)
    glVertex3f(-0.5,  0.5,  0.5) 
    glTexCoord2f(0.0, 0.5)
    glVertex3f(-0.5,  0.5, -0.5)

    glEnd()


def DrawGLScene():
    global xrot, yrot, zrot, textures, object, quadratic

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()					
    glTranslatef(0.0, 0.0, -5.0)			

    glRotatef(xrot, 1.0, 0.0, 0.0)			
    glRotatef(yrot, 0.0, 1.0, 0.0)			
    glRotatef(zrot, 0.0, 0.0, 1.0)		

    glBindTexture(GL_TEXTURE_2D, int(textures[0]))

    glEnable(GL_LIGHTING)
    DrawCube()
    glTranslatef(1.0, 1.0, -1.5)
    gluCylinder(quadratic,0.3,0.3, 0.3 ,32,32)

    xrot = xrot + 0.2				
    yrot = yrot + 0.2			
    zrot = zrot + 0.2

    glutSwapBuffers()


def main():
    global window
    glutInit(sys.argv)

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)

    glutInitWindowSize(640, 480)

    glutInitWindowPosition(0, 0)

    window = glutCreateWindow("Moving Objects with textures")

    glutDisplayFunc(DrawGLScene)

    glutIdleFunc(DrawGLScene)

    glutReshapeFunc(ReSizeGLScene)

    InitGL(640, 480)

    glutMainLoop()


if __name__ == "__main__":
    main()