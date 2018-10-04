#ifndef __FIRSTSYNTH__
#define __FIRSTSYNTH__

#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"

class FirstSynth : public IPlug
{
public:
  FirstSynth(IPlugInstanceInfo instanceInfo);
  ~FirstSynth();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mFrequency;
  void createPresets();
  Oscillator mOscillator;
};

#endif
