#ifndef __MIDIKEY__
#define __MIDIKEY__

#include "IPlug_include_in_plug_hdr.h"
#include "Oscillator.h"
#include "MIDIReceiver.h"

class MIDIKey : public IPlug
{
public:
  MIDIKey(IPlugInstanceInfo instanceInfo);
  ~MIDIKey();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessMidiMsg(IMidiMsg *pMsg);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mFrequency;
  MIDIReceiver mMIDIReceiver;
  void createPresets();
  Oscillator mOscillator;
};

#endif
