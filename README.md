# EnigmaMachine
Implementation of the Enigma Machine encryption algorithm with a simple command line interface to encrypt/decrypt a message.

 The original machine works according to the following:

 A machine consisting of a keyboard for input, a plugboard, reflector, rotors, and a message as output.

 PLUGBOARD: provides an initial scrambling, consisting of a socket corresponding for each letter on the keyboard.
 Each socket can be wired to a different letter, such that pressing O would yield P, for example, performing a simple character substitution.

 ROTORS: Next this key press input would pass through a series of rotors, which have as many characters as keys on the keyboard.
 These rotors are set to an initial setting, which is crucial for later decryption. Each time a key press input activates,
 the rotor mechanism increments before the character is enciphered
 The rotors perform character substitution, changing depending on the current configuration, with more rotors intensifying this effect.
 Everytime the rotors turn, this substitution configuration changes, such that pressing the same letter twice, i.e. "AA" will not yield
 the same character twice, i.e. "GE".

 REFLECTOR: The last critical component of the machine, the reflector is essentially like the plugboard, with letters connected to eachother in loops.
 After passing through the rotors, the character reaches the reflector, which performs character substitution and then passes its result back through the machine,
 passing through the rotors in reverse, and back through the plugboard, delivering its output and forming a reciprocal encryption loop,
 i.e. if you input "Hello" and receive "bAh!g" as output, and then set the rotor settings back to their initial settings, and input "bAh!g",
 you will receive the unencrypted "Hello" message.


 For simplicity, I keep the plugboard mappings the same for each run through; however this could be changed for future use.
 I set the reflector and rotors with a simple randomized mapping.

 To run the machine, simply run this as a command line app and follow the prompt.
