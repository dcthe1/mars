#include "vm/io.h"

namespace vm
{


IO* IOFactory::createIO( Setting& sett )
{
  std::string type;
  if ( (sett.lookupValue( "type", type )) && (type != "") ) {
    FactoryMap::iterator i = m_factorymap.find(type);
    if ( i->second != 0 ) {
      return (i->second)(sett);
    }
  }
  return 0;
}


void IOFactory::addIOClass( const std::string& className, iofactoryfunc factory )
{
  m_factorymap[className] = factory;
}


void IOFactory::clearIOClasses()
{
  m_factorymap.clear();
}


vmInt IO::readInt( unsigned int index )
{
	vmByte data[sizeof(vmInt)];
	for ( unsigned int i = 0; i < sizeof(vmInt); i++ ) data[i] = readByte(index+i);
	int* i = reinterpret_cast<int*>(data);
	return *i;
}


vmUInt IO::readUInt( unsigned int index )
{
	vmByte data[sizeof(vmUInt)];
	for ( unsigned int i = 0; i < sizeof(vmUInt); i++ ) data[i] = readByte(index+i);
	unsigned int* ui = reinterpret_cast<vmUInt*>(data);
	return *ui;
}


vmFloat IO::readFloat( unsigned int index )
{
	char data[sizeof(vmFloat)];
	for ( unsigned int i = 0; i < sizeof(vmFloat); i++ ) data[i] = readByte(index+i);
	vmFloat* f = reinterpret_cast<vmFloat*>(data);
	return *f;
}


vmBool IO::readBool( unsigned int index )
{
	vmByte by = readByte(index);
	vmBool* b = reinterpret_cast<vmBool*>(&by);
	return *b;
}


vmSByte IO::readSByte( unsigned int index )
{
	vmByte by = readByte(index);
	vmSByte* b = reinterpret_cast<vmSByte*>(&by);
	return *b;
}


void IO::writeInt( unsigned int index, const vmInt& data )
{
	const vmUInt* c = reinterpret_cast<const vmUInt*>(&data);
	writeUInt(index, *c );
}


void IO::writeUInt( unsigned int index, const vmUInt& data )
{
	const vmByte* c = reinterpret_cast<const vmByte*>(&data);
	for ( unsigned int i = 0; i < sizeof(data); i++ ) writeByte(index+i, c[i] );
}


void IO::writeFloat( unsigned int index, const vmFloat& data )
{
	const vmUInt* c = reinterpret_cast<const vmUInt*>(&data);
	writeUInt(index, *c );
}

void IO::writeBool( unsigned int index, const vmBool& data )
{
	const vmByte* c = reinterpret_cast<const vmByte*>(&data);
	writeByte(index, *c );
}

void IO::writeSByte( unsigned int index, const vmSByte& data )
{
	const vmByte* c = reinterpret_cast<const vmByte*>(&data);
	writeByte(index, *c );
}

NullIO& NullIO::nullIO()
{
  static NullIO n;
  return n;
}

}
