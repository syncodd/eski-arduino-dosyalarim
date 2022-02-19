import g4p_controls.*;
import processing.serial.*;

Serial Port;

int delayyy = 0;

public static final short portIndex = 0;  
public static final char LF = 10;

GPanel pMain, pLeft, pSerial;
GSlider2D sdr2D; 
GKnob gKnob;
GLabel kdLabel, gpsLabel, rotaLabel, statusLabel, tLabel;
GButton b1, b2, b3;
GLabel serialLabel;

int speedValue, xxx, yyy;
int numb = 0;

boolean b1Clicked, b2Clicked;
boolean modedddd = false;

String Txt;

void setup() {
  createGUI();
  
  try {
  println(" Connecting to -> " + Serial.list()[portIndex]);
  Port = new Serial(this,Serial.list()[portIndex], 9600);
  Txt = Port.readStringUntil(LF);  
  Txt = null;
  
  pSerial.setText("Serial Port (" + Serial.list()[portIndex] + ")");
  }
  catch(ArrayIndexOutOfBoundsException e) {
  println("!");
  }
}

void createGUI() {
  G4P.messagesEnabled(true);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  surface.setTitle("---");
  
  pMain = new GPanel(this, width/20+150, height/20, (width*9/10)-150, height*9/10, "MAIN");
  pMain.setText("Rota Belirleme Aracı");
  pMain.setOpaque(true);
  pMain.setCollapsible(modedddd);
  pMain.setDraggable(modedddd);
  pMain.setLocalColorScheme(GCScheme.RED_SCHEME);
  
  pLeft = new GPanel(this, 35, height/20, 150, height*9/10, "LEFT");
  pLeft.setText("Veri Okuma Aracı");
  pLeft.setOpaque(true);
  pLeft.setCollapsible(modedddd);
  pLeft.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  pLeft.setDraggable(modedddd);
  
  pSerial = new GPanel(this, 10, 300, 132, 250, "SERIAL");
  pSerial.setText("Serial Port " + "()");
  pSerial.setOpaque(true);
  pSerial.setCollapsible(true);
  pSerial.setLocalColorScheme(GCScheme.BLUE_SCHEME);
  pSerial.setDraggable(false);
  pLeft.addControl(pSerial);
  
  sdr2D = new GSlider2D(this, (width*9/10-150)/20, (height*9/10+100)/20, (height*9/10)*9/10, (height*9/10)*9/10);//((width*9/10)-150)*9/10
  sdr2D.setLimitsX(0.5, 0.0, 1.0);
  sdr2D.setLimitsY(0.5, 0.0, 1.0);
  sdr2D.setNumberFormat(G4P.DECIMAL, 2);
  sdr2D.setOpaque(false);
  sdr2D.setLocalColorScheme(GCScheme.RED_SCHEME);
  pMain.addControl(sdr2D);
  
  gKnob = new GKnob(this, 10, 30, 120, 120, 0.8);
  gKnob.setTurnRange(110, 70);
  gKnob.setTurnMode(GKnob.CTRL_VERTICAL);
  gKnob.setSensitivity(1);
  gKnob.setShowArcOnly(false);
  gKnob.setOverArcOnly(false);
  gKnob.setIncludeOverBezel(false);
  gKnob.setShowTrack(true);
  gKnob.setLimits(0.5, 0.0, 1.0);
  gKnob.setShowTicks(true);
  gKnob.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  gKnob.setOpaque(false);
  gKnob.setValue(0);
  pLeft.addControl(gKnob);
  
  serialLabel = new GLabel(this, 0, 0, 132, 250);
  serialLabel.setOpaque(false);
  serialLabel.setText("YER TUTUCU YAZI");
  pSerial.addControl(serialLabel);
  
  kdLabel = new GLabel(this, 37, 150, 80, 20);
  kdLabel.setOpaque(false);
  pLeft.addControl(kdLabel);
  
  gpsLabel = new GLabel(this, 50, 150, 180, 150);
  gpsLabel.setOpaque(false);
  pLeft.addControl(gpsLabel);
  
  statusLabel = new GLabel(this, width-175, 10, 175, 20);
  statusLabel.setOpaque(false);
  statusLabel.setText("Status : Try to connect...");
  statusLabel.setLocalColorScheme(4);
  
  b1 =  new GButton(this, 10, 570, 132, 50, "TEST");
  b1.setLocalColorScheme(GCScheme.YELLOW_SCHEME);
  pLeft.addControl(b1);
  
  b2 =  new GButton(this, 10, 625, 132, 50, "Servo TEST");
  b2.setLocalColorScheme(GCScheme.YELLOW_SCHEME);
  pLeft.addControl(b2);
  
  b3 =  new GButton(this, 700, 600, 132, 50, "Servo TEST");
  b3.setLocalColorScheme(GCScheme.YELLOW_SCHEME);
  pMain.addControl(b3);
}

void draw() {
  background(255);
  speedValue = (int)(gKnob.getValueF()*180);
  String textKnob = String.valueOf(speedValue);
  String textGPS = "X : " + (int)(sdr2D.getValueXF()*200-100) + "\nY : " + (int)(sdr2D.getValueYF()*200-100) + "\nmark ekle rota oluştur \n" + b1.hasFocus() + b1Clicked + b2Clicked;
    
  kdLabel.setText("Speed : " + textKnob);
  gpsLabel.setText(textGPS);
  
  try{
  if (Port.available() > 0) { 
      statusLabel.setText("Status : Connected");
      statusLabel.setLocalColorScheme(1);
      Txt = Port.readStringUntil(LF);
      if(Txt!=null) {
        serialLabel.setText(Txt);
      }
      delayyy = 0;
  } else {
    if(delayyy > 10) {
      statusLabel.setText("Status : !");
      statusLabel.setLocalColorScheme(3);
    }
    delayyy++;
  }
  }
  catch(NullPointerException e) {
  println("!!");
  }
  //serialTA.setText("asd\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void mousePressed() {
  if(b1.hasFocus()) {
    if(b1Clicked) {
      b1.setText("KUMANDA MODU");
      b1.setLocalColorScheme(GCScheme.RED_SCHEME);
      b1Clicked = false;
    } else {
      b1.setText("PANEL MODU");
      b1.setLocalColorScheme(GCScheme.GREEN_SCHEME);
      b1Clicked = true;
    }    
  }
  
  if(b2.hasFocus()) {
    if(b2Clicked) {
      b2.setText("Servo Test Durduruldu");
      b2.setLocalColorScheme(GCScheme.RED_SCHEME);
      b2Clicked = false;
    } else {
      b2.setText("Servo Test Başladı");
      b2.setLocalColorScheme(GCScheme.GREEN_SCHEME);
      b2Clicked = true;
    }    
  }
  
  if(b3.hasFocus()) {
      tLabel = new GLabel(this, ((width*9/10-150)/20+(((height*9/10)*9/10)*(sdr2D.getValueXF())))-5, ((height*9/10+100)/20+(((height*9/10)*9/10)*(sdr2D.getValueYF())))-5, 80,  20, "* Mark" + numb);
      tLabel.setOpaque(false);
      pMain.addControl(tLabel);
      numb++;
      
      line((int)tLabel.getX(), (int)tLabel.getY(), xxx, yyy);
      fill(0);
      xxx = (int)tLabel.getX();
      yyy = (int)tLabel.getY();
      
      try {
  println(" Connecting to -> " + Serial.list()[portIndex]);
  Port = new Serial(this,Serial.list()[portIndex], 9600);
  Txt = Port.readStringUntil(LF);  
  Txt = null;
  
  pSerial.setText("Serial Port (" + Serial.list()[portIndex] + ")");
  }
  catch(ArrayIndexOutOfBoundsException e) {
  println("!");
  }
  }
}

public void settings() {
  //fullScreen();
  size(1920, 1080);
}

/*if(sdr2D.hasFocus()) {
    tLabel = new GLabel(this, ((width*9/10-150)/20+(((height*9/10)*9/10)*(sdr2D.getValueXF()))), ((height*9/10+100)/20+(((height*9/10)*9/10)*(sdr2D.getValueYF()))), 80,  20, "asd");
    tLabel.setOpaque(false);
    pMain.addControl(tLabel);
  }*/
