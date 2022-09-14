/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/
/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("VideoPlayer");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAntiAliasing();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD

	/********************
	********************/
	setup_Gui();
	
	/********************
	********************/
	fbo_mov.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	ClearFbo(fbo_mov);
	
	/********************
	********************/
	VideoPlayer.load("mov/mov.mp4");
	
	VideoPlayer.setLoopState(OF_LOOP_NORMAL); // OF_LOOP_NONE, OF_LOOP_NORMAL
	VideoPlayer.setSpeed(1);
	VideoPlayer.setVolume(1.0);
	VideoPlayer.setPaused(false);
	// VideoPlayer.stop();
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	int now = ofGetElapsedTimeMillis();
	
	/********************
	********************/
	if(b_Seek){
		if(100 < now - t_KickSeek){
			b_Seek = false;
			VideoPlayer.play();
		}
	}else{
		if(Gui_Global->Video_Button_Start){
			Gui_Global->Video_Button_Start = false;
			VideoPlayer.play();
		}
		if(Gui_Global->Video_Button_Stop){
			Gui_Global->Video_Button_Stop = false;
			VideoPlayer.stop();
		}
		if(Gui_Global->Video_Button_Seek){
			Gui_Global->Video_Button_Seek = false;
			float pos = Gui_Global->Video_SeekPos;
			
			VideoPlayer.setPaused(true);
			VideoPlayer.setPosition(pos);
			
			b_Seek = true;
			t_KickSeek = now;
		}
		if(Gui_Global->Video_Button_TogglePause){
			Gui_Global->Video_Button_TogglePause = false;
			
			printf("\nisPaused : %d -> ", VideoPlayer.isPaused());
			if(VideoPlayer.isPaused())	VideoPlayer.setPaused(false);
			else						VideoPlayer.setPaused(true);
			printf("%d\n", VideoPlayer.isPaused());
			fflush(stdout);
		}
	}
	
	/********************
	********************/
	update_Video();
}

/******************************
******************************/
void ofApp::update_Video(){
	ofEnableAntiAliasing();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD
	
	VideoPlayer.update();
	if(VideoPlayer.isFrameNew()) {
		fbo_mov.begin();
			ofBackground(0);
			ofSetColor(255);
			VideoPlayer.draw(0, 0, fbo_mov.getWidth(), fbo_mov.getHeight());
		fbo_mov.end();
	}
	
	/********************
	********************/
	static int counter = 0;
	if(VideoPlayer.getIsMovieDone()){
		if(counter <= 0){
			printf("> movie is done\n");
			print_info();
			
			counter++;
		}
	}else{
		counter = 0;
	}
}


/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0);
	ofSetColor(255);
	
	/********************
	********************/
	fbo_mov.draw(0, 0, ofGetWidth(), ofGetHeight());
	if(VideoPlayer.isPlaying()) printf("%3.1f\r", VideoPlayer.getPosition());
	fflush(stdout);
	
	/********************
	********************/
	if(Gui_Global->b_Disp){
		Gui_Global->gui.draw();
	}
}

/******************************
******************************/
void ofApp::print_info(){
	printf("\n> info\n");
	if(VideoPlayer.isPlaying())	printf("getPosition = %3.2f\n", VideoPlayer.getPosition());
	else						printf("not playing now\n");
	
	printf("isPaused = %d\n", VideoPlayer.isPaused());
	printf("getIsMovieDone = %d\n", VideoPlayer.getIsMovieDone());
	printf("frame = %d / %d : %f\n", VideoPlayer.getCurrentFrame(), VideoPlayer.getTotalNumFrames(), (float)VideoPlayer.getCurrentFrame() / (float)VideoPlayer.getTotalNumFrames() );
	fflush(stdout);
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case 'd':
			Gui_Global->b_Disp = !Gui_Global->b_Disp;
			break;
			
		case ' ':
			print_info();
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
