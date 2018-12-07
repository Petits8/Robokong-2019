/*
 * EncoderPair.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: Jesus Velarde
 */

#include <EncoderPair.h>
#include <stdio.h>

EncoderPair::EncoderPair(int pinR1, int pinR2, int pinL1, int pinL2){
	rightEncoder = new Encoder(pinR1, pinR2, true, Encoder::EncodingType::k4X);
	rightEncoder->SetMaxPeriod(.1);
	rightEncoder->SetMinRate(10);
	rightEncoder->SetDistancePerPulse(5);
	rightEncoder->SetReverseDirection(true);
	rightEncoder->SetSamplesToAverage(7);
	rightEncoder->Reset();

	leftEncoder = new Encoder(pinL1, pinL2, false, Encoder::EncodingType::k4X);
	leftEncoder->SetMaxPeriod(.1);
	leftEncoder->SetMinRate(10);
	leftEncoder->SetDistancePerPulse(5);
	leftEncoder->SetReverseDirection(false);
	leftEncoder->SetSamplesToAverage(7);
	leftEncoder->Reset();

	timer = new Timer();
	rightPositionDelta = leftPositionDelta = rightPositionInitial = leftPositionInitial = rightVelocity = leftVelocity = 0.0;

}

void EncoderPair::Update(){

	rightPositionDelta = rightEncoder->GetDistance() - rightPositionInitial;
	leftPositionDelta = leftEncoder->GetDistance() - leftPositionInitial;

	double timeFinal = timer->Get();
	double timeDelta = timeFinal - timeInitial;

	if(timeDelta > 0.0){
		rightVelocity = rightPositionDelta/timeDelta;
		leftVelocity = leftPositionDelta/timeDelta;



	} else{
		DriverStation::ReportError("Time Zero Error");
	}

	timer->Reset();
	timer->Start();
	return;
}
