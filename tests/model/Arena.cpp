#include "Arena.h"

Arena::Arena()
	: BB_COMPILED(false)
{
}

void Arena::GraphicsSetup() {
	// Vertices
	#define VERTCOUNT 1538
	float bbverts[VERTCOUNT][3] =
		#include "../model/cube.verts"
	;
	
	// Generate vertex colors
	float bbvertcolor[VERTCOUNT][3];
	for (int i = 0; i < VERTCOUNT; ++i) {
		bbvertcolor[i][0] = .6;
		bbvertcolor[i][1] = .6;
		bbvertcolor[i][2] = .6;
	}
	
	// Faces (Quads)
	#define FACECOUNT 1536
	int bbfaces[FACECOUNT][4] = 
		#include "../model/cube.faces"
	;
	
	// Setup Display List for Bounding Box
	BB_DL = glGenLists(1);
	
	// Fill display list
	glNewList(BB_DL, GL_COMPILE);
	
	glColor3f(.6, .6, .6);
	
	// Material
	float _Ambient[4] = {.25f, .25f, .25f, 1.0f};
	float _Diffuse[4] = {.4f, .4f, .4f, 1.0f};
	float _Specular[4] = {0.774597f, 0.774597f, 0.774597f, 1};
	float _Shininess = 76.8f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _Diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _Specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _Shininess);
    
    /*
    // LIGHTS
	GLfloat ambientcolor[] = {.6, .6, .6, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	
	GLfloat light0pos[4];
	GLfloat light0dif[4];
	GLfloat light1pos[4];
	GLfloat light1dif[4];
	GLfloat light2pos[4];
	GLfloat light2dif[4];
	GLfloat light3pos[4];
	GLfloat light3dif[4];
	
	glEnable(GL_LIGHT0);
		light0pos[0] = 0; light0pos[1] = 0; light0pos[2] = 1; light0pos[3] = 1;
		light0dif[0] = .3; light0dif[1] = .15; light0dif[2] = .15; light0dif[3] = 1;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
	glEnable(GL_LIGHT1);
		light1pos[0] = 5; light1pos[1] = -2; light1pos[2] = 8; light1pos[3] = 1;
		light1dif[0] = .3; light1dif[1] = .8; light1dif[2] = .1; light1dif[3] = 1;
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
	glEnable(GL_LIGHT2);
		light2pos[0] = -2; light2pos[1] = 10; light2pos[2] = -1; light2pos[3] = 1;
		light2dif[0] = .3; light2dif[1] = .2; light2dif[2] = 1;  light2dif[3] = 1;
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
	glEnable(GL_LIGHT3);
		light3pos[0] = -140; light3pos[1] = -110; light3pos[2] = 70; light3pos[3] = 1;
		light3dif[0] = .3; light3dif[1] = 0; light3dif[2] = 0;  light3dif[3] = 1;
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light3dif);
    // \LIGHTS
    */
    
	glBegin(GL_QUADS);
	for (int f = 0; f < FACECOUNT; f++) { // face
		for (int p = 0; p < 4; p++) { // point on face (quad)
			
			// Randomize Color
			glColor3f(bbvertcolor[bbfaces[f][p]-1][0], bbvertcolor[bbfaces[f][p]-1][1], bbvertcolor[bbfaces[f][p]-1][2]);
			
			// Draw Vertex
			glVertex3f(
				  bbverts[bbfaces[f][p]-1][0]
				, bbverts[bbfaces[f][p]-1][1]
				, bbverts[bbfaces[f][p]-1][2]
			);
//			std::cout << "f: " << f << "\tp: " << p << "\n";
//			std::cout << 
//				"\tx: " << bbverts[bbfaces[f][p-1]][0] << 
//				"\ty: " << bbverts[bbfaces[f][p-1]][1] <<
//				"\ty: " << bbverts[bbfaces[f][p-1]][2] <<
//			"\n";
		}
	}
	glEnd();		
	
	glColor3f(.6, .6, .6);
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0, .1, 0);
		glVertex3f(.1, .1, 0);
		glVertex3f(.1, 0, 0);
	glEnd();
	
	glEndList();
	
	#undef VERTCOUNT
	#undef FACECOUNT
	
	BB_COMPILED = true;
}

void Arena::Update () {	
	vector<Pushable*> sphericals;
	sphericals.insert( sphericals.end(), Orbs.begin(), Orbs.end() );
	sphericals.insert( sphericals.end(), Ships.begin(), Ships.end() );
	
	vector<Pushable*> tractorables;
	tractorables.insert( tractorables.end(), Orbs.begin(), Orbs.end() );
	tractorables.insert( tractorables.end(), Ships.begin(), Ships.end() );
	
	vector<Pushable*> boundables;
	boundables.insert( boundables.end(), Orbs.begin(), Orbs.end() );
	boundables.insert( boundables.end(), Ships.begin(), Ships.end() );
	
	// Collision section
	// Collide sphericals
	for (vector<Pushable*>::iterator itA = sphericals.begin(); itA != sphericals.end(); ++itA) {
		for(vector<Pushable*>::iterator itB = itA; ++itB != sphericals.end();) {
			FluffyCollideSpheres( *itA, *itB );
		}
	}
	
	// Bounding Box
	for(std::vector<Pushable*>::iterator it = boundables.begin(); it != boundables.end(); ++it) {
		CollideBounds(*it);
	}
	
	// Update Strands
	for(std::vector<Strand*>::iterator it = Strands.begin(); it != Strands.end(); ++it) {
		(**it).Update();
	}
	
	// Update Orbs
	for(std::vector<Orb*>::iterator it = Orbs.begin(); it != Orbs.end(); ++it) {
		(**it).Update();
	}

	// Update Ships
	for(std::vector<Ship*>::iterator it = Ships.begin(); it != Ships.end(); ++it) {
		(**it).Update();
		(**it).PaintTargets(Orbs);
		(**it).TractorEffect(tractorables);
	}	
}

void Arena::Render() {
	// Strands
	for(std::vector<Strand*>::iterator it = Strands.begin(); it != Strands.end(); ++it) {
		(**it).Render();
	}
	
	// Orbs
	for(std::vector<Orb*>::iterator it = Orbs.begin(); it != Orbs.end(); ++it) {
	
		(**it).Render();
	}
	
	// Render Bounds
//	glutSolidCube(200);
	
	glColor3f(.6, .6, .6);
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(1, 0, 0);
	glEnd();
	
	glPushMatrix();
	glScalef(50, 50, 50);
	glCallList(BB_DL);
	glPopMatrix();
}

/// Uses fluffy collision.\n
/// If objects are intersecting, use a spring from the farthest intersecting surface.
bool Arena::FluffyCollideSpheres (Pushable* A, Pushable* B) {
	// Information
	float distance = (A->Pos - B->Pos).Length();
	float mindist = (A->Rad + B->Rad);
	
	// Do nothing if there is no collision
	if ( distance > mindist ) {
		return false;
	}
	
	V3D ColAxis = (A->Pos - B->Pos).Normalized();
	
	// Fluffy collision
	float k = 6.1; // Fluffiness constant
	A->PushGlobal( ColAxis * (distance-mindist) * -k );
	B->PushGlobal( ColAxis * (distance-mindist) * k );
	return true;
}

/* DEPRECATED physically accurate collision
	
	// One Dimensional Collision
	// http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
	float mA = A->Mass;
	float mB = B->Mass;
	float uA = A->Vel.Dot(ColAxis); // Starting velocity of A
	float uB = B->Vel.Dot(ColAxis); // Starting velocity of B
	
	// Calculate new velocities
	float vA = ( (uA*(mA-mB)) + (2*mB*uB) ) / (mA + mB); // Final 1d velocity of A
	float vB = ( (uB*(mB-mA)) + (2*mA*uA) ) / (mA + mB); // Final 1d velocity of B
	
	// Zero velocity in collision axis
	A->Vel -= ColAxis * uA;
	B->Vel -= ColAxis * uB;
	
	// Apply calculated velocities
	A->Vel += ColAxis * vA;
	B->Vel += ColAxis * vB;
*/

bool Arena::CollideBounds (Pushable* obj) {
	bool hit = false;
	float rad = (*obj).Rad;
	
	// X
	if ( (*obj).Pos.x - rad < -100 ) {
		(*obj).Vel.x = fabs((*obj).Vel.x);
		(*obj).Pos.x = -100 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.x + rad > 100 ) {
		(*obj).Vel.x = -fabs((*obj).Vel.x);
		(*obj).Pos.x = 100 - rad;
		hit = true;
	}
	
	// Y
	if ( (*obj).Pos.y - rad < -100 ) {
		(*obj).Vel.y = fabs((*obj).Vel.y);
		(*obj).Pos.y = -100 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.y + rad > 100 ) {
		(*obj).Vel.y = -fabs((*obj).Vel.y);
		(*obj).Pos.y = 100 - rad;
		hit = true;
	}
	
	// Z
	if ( (*obj).Pos.z - rad < -100 ) {
		(*obj).Vel.z = fabs((*obj).Vel.z);
		(*obj).Pos.z = -100 + rad;
		hit = true;
	} else
	if ( (*obj).Pos.z + rad > 100 ) {
		(*obj).Vel.z = -fabs((*obj).Vel.z);
		(*obj).Pos.z = 100 - rad;
		hit = true;
	}
	
	// Wall Friction (..., yeah, that)
	if (hit) {
		(*obj).Vel *= .9;
	}
	
	return hit;
}
