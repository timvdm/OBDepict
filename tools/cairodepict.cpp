#include <openbabel/obconversion.h>
#include <openbabel/mol.h>

#include <OBDepict>
#include <cairopainter.h>

#include <iostream>
using namespace std;

using namespace OpenBabel;

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
    return -1;
  }

  // read a molecule
  OBConversion conv;
  OBFormat *format = conv.FormatFromExt(argv[1]);
  conv.SetInFormat(format);

  std::string filename(argv[1]);
  std::ifstream ifs;
  ifs.open(filename.c_str());
  if (!ifs) {
    std::cerr << "Could not open " << filename << std::endl;
    return -1;
  }

  CairoPainter *painter = new CairoPainter;
  OBDepict depictor(painter);
 
  string::size_type pos = filename.find_last_of(".");
  if (pos != string::npos)
    filename = filename.substr(0, pos);

  OBMol mol;
  unsigned int count = 1;
  while (conv.Read(&mol, &ifs)) {
    // depict the molecule
    depictor.DrawMolecule(&mol);
    depictor.AddAtomLabels(OBDepict::AtomSymmetryClass);
    
    std::stringstream ss;
    ss << filename << count << ".png";
    painter->WriteImage(ss.str());

    count++;
  }

  return 0;
}
