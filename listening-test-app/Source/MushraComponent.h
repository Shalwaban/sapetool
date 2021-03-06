#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscTransceiver.h"
#include "SampleRegion.h"
#include <vector>
#include <random>

using std::vector;

class MushraComponent : public Component,
						public Button::Listener,
						public Slider::Listener,
						public OSCReceiver,
						public OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>
{
public:
	//==============================================================================
	MushraComponent();
	~MushraComponent();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	OwnedArray<SampleRegion> regionArray;
	vector<vector<float>> scoresArray;
	vector<int> trialRandomizationArray;
	vector<vector<int>> sampleRandomizationArray;
	Array<String> trackNameArray;
	bool randomizeSamples = true;
	int numberOfSamplesPerRegion;
	String hostIp;
	int clientRxPortAtHost;
	void createGui();
	void connectOsc(String dawIp, String clientIp, int dawTxPort, int dawRxPort, int clientTxPort, int clientRxPort);
	void initClientGui();
	void saveResults();

private:
	oscTransceiver dawTx, dawRx;
	oscTransceiver clientTx, clientRx;

	// APP CONFIG
	bool isReferenceButtonVisible = true;


	// APP STATE
	int currentRegion = 0, currentTrack = 0;
	int currentTrialIndex = 0;
	float currentPosition;
	bool playback = false;
	bool loop = true;
	Label dawTimeLabel, sampleTimeLabel;

	// MUSHRA CONTROLS
	TextButton playReference;
	TextButton stopPlaybackB;
	TextButton goToPrevious, goToNext;
	OwnedArray<Slider> rateSampleSliderArray;
    OwnedArray<Label> rateSampleSliderLabelArray;
	OwnedArray<Button> playSampleButtonArray;
	Slider loopSlider;
	ToggleButton loopTB;
	
	// METHODS
	void playSample(int track, bool randomize);
	void playSampleLoop();
	void stopPlayback();
	void buttonClicked(Button* buttonThatWasClicked) override;
	void sliderValueChanged(Slider *sliderThatWasChanged) override;
	void oscMessageReceived(const OSCMessage& message) override;
	void updateTransportSlider(bool updateLoop);
	void updateClientRatingSliders();
	void updateClientTransportSlider();
	void updateRatingSliders();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MushraComponent)
};
