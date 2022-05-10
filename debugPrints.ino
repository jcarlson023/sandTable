void printFileReads() {
  Serial.print(String(nextStepsLin) + ", ");
  Serial.print(String(nextStepsRot) + ", ");
  Serial.print(String(nextPrescalarLin) + ", ");
  Serial.print(String(nextPrescalarRot) + ", ");
  Serial.print(String(nextCmrLin) + ", ");
  Serial.println(String(nextCmrRot));
}

void printCurr() {
  Serial.println("Curr parameters:");
  Serial.println("stepsRot: " + String(stepsRot));
  Serial.println("stepsLin: " + String(stepsLin));
  Serial.println("currRot: " + String(currRot));
  Serial.println("currLin: " + String(currLin));
  Serial.println("rot cmr: " + String(nextCmrRot));
  Serial.println("lin cmr: " + String(nextCmrLin));
  Serial.println(" ");
}
