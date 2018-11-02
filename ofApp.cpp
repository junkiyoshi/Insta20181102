#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofNoFill();
	ofBackground(39);
	ofSetColor(239);
	ofSetLineWidth(3);

	this->font_size = 300;
	this->font.loadFont("fonts/Kazesawa-Regular.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	SYSTEMTIME sys_time;
	GetSystemTime(&sys_time);

	int second = sys_time.wSecond;
	int sample_count = 100;
	int step = ofMap(sys_time.wMilliseconds, 0, 1000, 0, sample_count * 2);
	bool close = false;
	
	std::ostringstream sout;
	sout << setfill('0') << setw(2) << second;
	string word = sout.str();
	char charactors[2];
	word.copy(charactors, 2);

	ofTranslate(this->font_size * 0.35, ofGetHeight() * 0.5 + this->font_size * 0.5);

	for (int charactor_index = 0; charactor_index < 2; charactor_index++) {

		ofPath path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			ofBeginShape();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);

				close = false;
				if(charactor_index == 0)
				{
					if (second % 10 != 0) {

						ofVertex(point);
						close = true;
					}
					else {

						if (step < sample_count) {

							if (vertices_index < step % sample_count) {

								ofVertex(point);
							}

							if (vertices_index == step % sample_count) {

								ofDrawCircle(point, 3);
							}
						}
						else {

							ofVertex(point);
							close = true;
						}
					}
				}
				else {

					if (step < sample_count) {

						if (vertices_index < step % sample_count) {

							ofVertex(point);
						}
					}
					else {

						if (vertices_index > step % sample_count) {

							ofVertex(point);
						}
					}

					if (vertices_index == step % sample_count) {

						ofDrawCircle(point, 3);
					}
				}
			}
			ofEndShape(close);
		}

		ofTranslate(this->font_size, 0);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}