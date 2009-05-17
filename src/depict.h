#ifndef OB_DEPICT_H
#define OB_DEPICT_H

#include <openbabel/babelconfig.h>
#include <openbabel/math/vector3.h>

namespace OpenBabel
{

  class OBMol;
  class OBPainter;
  class OBDepictPrivate;
  class OBAPI OBDepict
  {
    public:
      enum AtomLabelType {
        AtomId = 1,
        AtomIndex,
        AtomSymmetryClass,
        AtomValence,
        AtomTetrahedralStereo
      };

      /**
       * Constructor.
       */
      OBDepict(OBPainter *painter);
      /**
       * Draw @p mol using the painter previously stored in the constructor.
       *
       * @return True if successful.
       */
      bool DrawMolecule(OBMol *mol);
      /**
       * Draw atom labels of a specified @p type. 
       *
       * @return True if successful. 
       */
      bool AddAtomLabels(AtomLabelType type);

      void SetBondLength(double length); 
      double GetBondLength() const;

      void SetPenWidth(double length); 
      double GetPenWidth() const;

      void SetBondSpacing(double spacing); 
      double GetBondSpacing() const;

      void SetBondWidth(double width); 
      double GetBondWidth() const;

      void SetDrawingTerminalCarbon(bool enabled);
      bool GetDrawingTerminalCarbon() const;

      void SetFontFamily(const std::string &family); 
      const std::string& GetFontFamily() const;

      void SetFontSize(int pointSize, bool subscript = false);
      int GetFontSize(bool subscript = false) const;

    private:
      OBDepictPrivate * const d;
  };

}

#endif
