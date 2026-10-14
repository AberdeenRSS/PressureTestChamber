
#include <commands.h>
#include <chamber_state_machine.h>

char commandReadBuffer[SerialBufferSize];

int commandReadBufferIndex;

bool checkCommand(String commandName, unsigned int length, String cmd){

  if(cmd.length() >= length && cmd.startsWith(commandName)){
    return true;
  }
  return false;

}

IntCommandOut checkIntCommand(String commandName, unsigned int length, String cmd){

  if(cmd.length() > length && cmd.startsWith(commandName)){

    int value = cmd.substring(length-1, cmd.length()).toInt();
    return { true, value };

  }
  return { false, 0 };

}

void processCommands(){

  // Converting read buffer to char* is safe
  // as it is null terminated
  String cmd = String((char*) commandReadBuffer);

  // Treat commands case invariant
  cmd.toUpperCase();

  if(checkCommand("VENT", 4, cmd)){
    vent();
    return;
  }

  if(checkCommand("HOLD", 4, cmd)){
    hold();
    return;
  }

  if(checkCommand("PMPD", 4, cmd)){
    pumpDown();
    return;
  }

  IntCommandOut res = checkIntCommand("ACND_RATE ", 10, cmd);

  if(res.success){
    ascendAtRate(res.value);
    return;
  }
}

void readSerial()
{

  // Serial command processing
  int available = Serial.available();
  if(available){

    while(--available > 0){

      char c = Serial.read();

      // Reset serial read buffer if we are at a new line
      // Works for both CR LF and LF
      if(c == 0x0A || c == 0x0D){
        commandReadBufferIndex = 0;
        continue;
      }

      // Command too long
      if (commandReadBufferIndex > 28)
        continue;

      // Command ends with ';', process command in this case
      // and ready for next command
      if (c == ';'){
        commandReadBuffer[commandReadBufferIndex] = '\0'; // Insert null terminator
        processCommands();
        commandReadBufferIndex = 0;
        continue;
      }

      commandReadBuffer[commandReadBufferIndex++] = c;
    }

  }

}
