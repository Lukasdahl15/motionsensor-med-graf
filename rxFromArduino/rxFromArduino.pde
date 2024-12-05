import processing.serial.*;
//Start seriel kommunikation
Serial port; // USB-portens navn
String USBPort = "COM7";

// Variables for Graph
int[] distances;         // Array to store graph data
int graphIndex = 0;      // Index for storing graph data


void setup() {
  // Koden til afvikles en gang, når programmet startes
  size(800, 800);
  background(80);
  frameRate(60);
  textSize(24);
  // Starter den serielle port
  port = new Serial(this, USBPort, 9600);

  // Initialize distances array
  distances = new int[width];
}

String tekst = "";
float distance = 0;

void draw() {
  // Kode der kaldes med programmets framerate
  // Start på en frisk i hver frame
  background(40);
   rect(0, 0, width - 1, height - 1);
  for (int i = 0; i < distances.length - 1; i++) {
    line(i, height - distances[i], i + 1, height - distances[i + 1]);
  }
  // Draw the graph
  stroke(0, 0, 255);
  if (port.available() > 0) {
    tekst = port.readStringUntil('\n');
    tekst = trim(tekst);
    if (tekst != null) {
      tekst = trim(tekst);
      try {
        // Parse the distance value
        distance = float(tekst);

        // Store the distance in the array for graphing
        distances[graphIndex] = int(map(distance, 0, 100, 0, height)); // Map to graph height
        graphIndex = (graphIndex + 1) % distances.length; // Loop around
      }
      catch (NumberFormatException e) {
        println("Error parsing data: " + tekst);
      }
    }
  }
}

// Mouse service rutiner
void mouseClicked() {
}

void mousePressed() {
}

void mouseReleased() {
}

// Keyboard service routines
void keyPressed() {
}

void keyReleased() {
}

void keyTyped() {
}
