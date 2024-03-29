// Our transformation class PVSS <--> Hardware
#include <demoTrans.hxx>
#include <ErrHdl.hxx>     // The Error handler Basics/Utilities
#include <TextVar.hxx>    // Our Variable type Basics/Variables
#include <demoTransformationType.hxx>

#include <stdio.h>

//----------------------------------------------------------------------------

TransformationType demoTrans::isA() const
{
  // TODO
  return demoTransformationType::Undefined;
}


//----------------------------------------------------------------------------

Transformation *demoTrans::clone() const
{
  // TODO
  return new demoTrans(varType);
}

//----------------------------------------------------------------------------
// Our item size. The max we will use is 256 Bytes.
// This is an arbitrary value! A Transformation for a long e.g. would return 4

int demoTrans::itemSize() const
{
  // TODO
  return 256;
}

//----------------------------------------------------------------------------
// Our preferred Variable type. Data will be converted to this type
// before toPeriph is called.

VariableType demoTrans::getVariableType() const
{
  // TODO
  return TEXT_VAR;
}

//----------------------------------------------------------------------------
// Convert data from PVSS to Hardware.
// In this example the subindex is ignored

PVSSboolean demoTrans::toPeriph(PVSSchar *buffer, PVSSushort len,
                                      const Variable &var, const PVSSushort subix) const
{
  // TODO  everything in here has to be adapted to your needs

  // Be paranoic, check variable type
  if ( var.isA() != TEXT_VAR )
  {
    // Throw error message
    ErrHdl::error(
      ErrClass::PRIO_SEVERE,             // Data will be lost
      ErrClass::ERR_PARAM,               // Wrong parametrization
      ErrClass::UNEXPECTEDSTATE,         // Nothing else appropriate
      "demoTrans", "toPeriph",     // File and function name
      "Wrong variable type for data"     // Unfortunately we don't know which DP
    );

    return PVSS_FALSE;
  }

  // Check data len. TextVar::getString returns a CharString
  if (len < static_cast<const TextVar &>(var).getString().len() + 1)
  {
    // Throw error message
    ErrHdl::error(
      ErrClass::PRIO_SEVERE,             // Data will be lost
      ErrClass::ERR_IMPL,                // Mus be implementation
      ErrClass::UNEXPECTEDSTATE,         // Nothing else appropriate
      "demoTrans::toPeriph",       // File and function name
      "Data buffer too small; need:" +
      CharString(static_cast<const TextVar &>(var).getString().len() + 1) +
      " have:" + CharString(len)
    );

    return PVSS_FALSE;
  }

  sprintf(reinterpret_cast<char *>(buffer), "%s", static_cast<const TextVar &>(var).getValue());

  return PVSS_TRUE;
}

//----------------------------------------------------------------------------
// Conversion from Hardware to PVSS

VariablePtr demoTrans::toVar(const PVSSchar *buffer, const PVSSushort dlen,
                                   const PVSSushort /* subix */) const
{
  // TODO  everything in here has to be adapted to your needs

  // Return pointer to new PVSS Variable
  Variable *var = Variable::allocate(varType);

  (*var) = TextVar(reinterpret_cast<const char *>(buffer));   // virtual operator= in all Variables

  return var;
}

//----------------------------------------------------------------------------
