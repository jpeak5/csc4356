/* Copyright (c) 2010 Robert Kooima                                           */
/*                                                                            */
/* Permission is hereby granted, free of charge, to any person obtaining a    */
/* copy of this software and associated documentation files (the "Software"), */
/* to deal in the Software without restriction, including without limitation  */
/* the rights to use, copy, modify, merge, publish, distribute, sublicense,   */
/* and/or sell copies of the Software, and to permit persons to whom the      */
/* Software is furnished to do so, subject to the following conditions:       */
/*                                                                            */
/* The above copyright notice and this permission notice shall be included in */
/* all copies or substantial portions of the Software.                        */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    */
/* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        */
/* DEALINGS IN THE SOFTWARE.                                                  */

#ifndef UTIL3D_GL_H
#define UTIL3D_GL_H

/*----------------------------------------------------------------------------*/
/* Include the current platform's headers for GL, GLUT, and GLEW              */

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_OS_IPHONE
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#ifdef __APPLE__
#include   <GL/glew.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include   <GL/glew.h>
#include   <GL/glut.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* Homogenize some of the quirks of OpenGL ES                                 */

#ifdef GL_OES_VERSION_1_0
#define glFrustum glFrustumf
#define glOrtho   glOrthof
#endif

/*----------------------------------------------------------------------------*/

#if TARGET_OS_IPHONE
#include "GLUtility.h"
#else
#define FILENAME(s) s
#endif

/*----------------------------------------------------------------------------*/

#endif
