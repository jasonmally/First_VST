#include "MIDIKey.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

enum EParams
{
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT
};

MIDIKey::MIDIKey(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mFrequency(1.)
{
  TRACE;

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachPanelBackground(&COLOR_GREEN);
  AttachGraphics(pGraphics);
  createPresets();
}

MIDIKey::~MIDIKey() {}

void MIDIKey::ProcessMidiMsg(IMidiMsg *pMsg)
{
	mMIDIReceiver.onMessageReceived(pMsg);
}

void MIDIKey::ProcessDoubleReplacing(
	double** inputs,
	double** outputs,
	int nFrames)
{
	// Mutex is already locked for us.

	double *leftOutput = outputs[0];
	double *rightOutput = outputs[1];

	for (int i = 0; i < nFrames; ++i) {
		mMIDIReceiver.advance();
		int velocity = mMIDIReceiver.getLastVelocity();
		if (velocity > 0) {
			mOscillator.setFrequency(mMIDIReceiver.getLastFrequency());
			mOscillator.setMuted(false);
		}
		else {
			mOscillator.setMuted(true);
		}
		leftOutput[i] = rightOutput[i] = mOscillator.nextSample() * velocity / 127.0;
	}

	mMIDIReceiver.Flush(nFrames);
}

void MIDIKey::Reset()
{
  TRACE;
  IMutexLock lock(this);
  mOscillator.setSampleRate(GetSampleRate());
}

void MIDIKey::createPresets()
{
	MakeDefaultPreset((char *) "-", kNumPrograms);
}

void MIDIKey::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

}
