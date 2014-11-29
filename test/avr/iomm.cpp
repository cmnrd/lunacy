#include <avr/iomm.hpp>
using namespace Lunacy;

using PORTD = IOMMPtr<uint8_t, 0x32>;
using PORTB = IOMMPtr<uint8_t, 0x38>;

int main()
{
  PORTD::write(0x01);
  PORTD::write(0x20);

  PORTB::deref() = 0;
  PORTB::deref() = PORTD::deref() + 3;

  while(true);

  return 0;
}
