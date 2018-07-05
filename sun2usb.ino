static byte keyStack[6];
//TODO handle stack overflow
byte addToKeyStack( char key ){
  for( int i = 0; i < 6; i++ ){
    if( keyStack[i] == 0 ){
      keyStack[i] = key;
      return 1;
    }
  }
  return 0;
}
//TODO handle mismatched character
byte dropFromKeyStack( char key ){
  for( int i = 0; i < 6; i++ ){
    if( keyStack[i] == key ){
      keyStack[i] = 0;
      return 1;
    }
  }
  return 0;
}
//TODO add keyboard beeper test code
//TODO add keyboard beeper code to respond to exceptions
void setup(){
  SerialUSB.begin( 9600 );
  while( !SerialUSB );
  Serial1.begin( 1200 );
}

void loop(){
  while( Serial1.available() > 0 ){
    byte in = Serial1.read();
    static byte mod = 0;
    SerialUSB.println( in );
    switch( in ){
      case 76:
        mod |= MODIFIERKEY_CTRL;
        break;
      case 204:
        mod &= ~MODIFIERKEY_CTRL;
        break;
      case 102:
        addToKeyStack( KEY_C );
        break;
      case 230:
        dropFromKeyStack( KEY_C );
        break;
    }
    Keyboard.set_modifier( mod );
    Keyboard.set_key1( keyStack[0] );
    Keyboard.set_key2( keyStack[1] );
    Keyboard.set_key3( keyStack[2] );
    Keyboard.set_key4( keyStack[3] );
    Keyboard.set_key5( keyStack[4] );
    Keyboard.set_key6( keyStack[5] );
    Keyboard.send_now();
  }
}
