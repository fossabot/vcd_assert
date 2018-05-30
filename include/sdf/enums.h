#ifndef LIBSDF_ENUMS_H_
#define LIBSDF_ENUMS_H_

#include <parse/grammar/base.h>

namespace SDF {

enum class TimescaleUnit {
  s, ms, us, ns, ps
};

enum class TimescaleNumber {
  _1, _10, _100
};

enum class TimingSpecType {
  delay,
  timingCheck,
  timingEnv,
  label
};

enum class TimingCheckType {
  setup,
  hold,
  setuphold,
  recovery,
  removal,
  recrem,
  skew,
  bidirectskew,
  width,
  period,
  nochange
};

enum class DataType {
  value,
  triple,
  rvalue,
  rtiple,
  delval,
  delval_list,
  retval
};

enum class DelayType{
  iopath,
  interconnects
};


} // namespace SDF

#endif // LIBSDF_ENUMS_H_
