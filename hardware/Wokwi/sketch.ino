#define STATUS_LED     2
#define CURTAIL_CTRL   25
#define EXPORT_CTRL    26
#define IMPORT_CTRL    27

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  pinMode(CURTAIL_CTRL, OUTPUT);
  pinMode(EXPORT_CTRL, OUTPUT);
  pinMode(IMPORT_CTRL, OUTPUT);

// Start with everything OFF (safe state)
  digitalWrite(STATUS_LED, LOW);
  digitalWrite(CURTAIL_CTRL, LOW);
  digitalWrite(EXPORT_CTRL, LOW);
  digitalWrite(IMPORT_CTRL, LOW);

  Serial.begin(115200);
  Serial.println("GPIO Test Started...");
}

void loop() {
  // 1. Status LED
  Serial.println("Status LED ON");
  digitalWrite(STATUS_LED, HIGH);
  delay(800);
  digitalWrite(STATUS_LED, LOW);
  delay(400);

  // 2. Curtailment
  Serial.println("Curtailment ON");
  digitalWrite(CURTAIL_CTRL, HIGH);
  delay(800);
  digitalWrite(CURTAIL_CTRL, LOW);
  delay(400);

  // 3. Export
  Serial.println("Export ON");
  digitalWrite(EXPORT_CTRL, HIGH);
  delay(800);
  digitalWrite(EXPORT_CTRL, LOW);
  delay(400);

  // 4. Import
  Serial.println("Import ON");
  digitalWrite(IMPORT_CTRL, HIGH);
  delay(800);
  digitalWrite(IMPORT_CTRL, LOW);
  delay(400);

  delay(1000);
}