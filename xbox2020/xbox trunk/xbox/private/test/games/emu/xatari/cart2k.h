#ifndef CARTRIDGE2K_HXX
#define CARTRIDGE2K_HXX

class Cartridge2K;
class System;

#include "bspf.h"
#include "Cart.h"

/**
  This is the standard Atari 2K cartridge.  These cartridges 
  are not bankswitched, however, the data repeats twice in the 
  2600's 4K cartridge addressing space.

  @author  Bradford W. Mott
  @version $Id: Cart2K.hxx,v 1.2 1998/07/15 20:50:57 bwmott Exp $
*/
class Cartridge2K : public Cartridge
{
  public:
    /**
      Create a new cartridge using the specified image

      @param image Pointer to the ROM image
    */
    Cartridge2K(const uInt8* image);
 
    /**
      Destructor
    */
    virtual ~Cartridge2K();

  public:
    /**
      Get a null terminated string which is the device's name (i.e. "M6532")

      @return The name of the device
    */
    virtual const char* name() const;

    /**
      Reset cartridge to its power-on state
    */
    virtual void reset();

    /**
      Install cartridge in the specified system.  Invoked by the system
      when the cartridge is attached to it.

      @param system The system the device should install itself in
    */
    virtual void install(System& system);

  public:
    /**
      Get the byte at the specified address

      @return The byte at the specified address
    */
    virtual uInt8 peek(uInt16 address);

    /**
      Change the byte at the specified address to the given value

      @param address The address where the value should be stored
      @param value The value to be stored at the address
    */
    virtual void poke(uInt16 address, uInt8 value);

  private:
    // The 2k ROM image for the cartridge
    uInt8 myImage[2048];
};
#endif

