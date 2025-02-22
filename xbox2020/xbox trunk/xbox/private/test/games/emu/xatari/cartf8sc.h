#ifndef CARTRIDGEF8SC_HXX
#define CARTRIDGEF8SC_HXX

class CartridgeF8SC;

#include "bspf.h"
#include "Cart.h"

/**
  Cartridge class used for Atari's 8K bankswitched games with
  128 bytes of RAM.  There are two 4K banks.

  @author  Bradford W. Mott
  @version $Id: CartF8SC.hxx,v 1.2 1998/07/15 20:30:51 bwmott Exp $
*/
class CartridgeF8SC : public Cartridge
{
  public:
    /**
      Create a new cartridge using the specified image

      @param image Pointer to the ROM image
    */
    CartridgeF8SC(const uInt8* image);
 
    /**
      Destructor
    */
    virtual ~CartridgeF8SC();

  public:
    /**
      Get a null terminated string which is the device's name (i.e. "M6532")

      @return The name of the device
    */
    virtual const char* name() const;

    /**
      Reset device to its power-on state
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
      Get the byte at the specified address.

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
    /**
      Install pages for the specified bank in the system

      @param bank The bank that should be installed in the system
    */
    void bank(uInt16 bank);

  private:
    // Indicates which bank is currently active
    uInt16 myCurrentBank;

    // The 8K ROM image of the cartridge
    uInt8 myImage[8192];

    // The 128 bytes of RAM
    uInt8 myRAM[128];
};
#endif

