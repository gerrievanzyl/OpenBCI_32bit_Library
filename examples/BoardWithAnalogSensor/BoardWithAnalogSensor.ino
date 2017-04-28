#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Notify the board we want to use aux data, this effects `::sendChannelData()`
  board.useAccel(false);
}

void loop() {

  // The main dependency of this single threaded microcontroller is to
  //  stream data from the ADS.
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

      // Read from the analog sensor and store auxiliary position 0
      // take a reading from the ADC. Result range from 0 to 1023
      board.auxData[0] = analogRead(A7);

      // Send standard packet with channel data and aux data
      //  includes aux data because we set `useAux` in setup()
      board.sendChannelData();
    }
  }

  // Check the serial port for new data
  if (board.hasDataSerial0()) {
    // Read one char and process it
    board.processChar(board.getCharSerial0());
  }
}
