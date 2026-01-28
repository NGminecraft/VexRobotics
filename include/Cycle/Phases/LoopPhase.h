#pragma once
class LoopPhase {
public:
	LoopPhase() = default;
	virtual ~LoopPhase() = default;

	virtual void execute(const unsigned long tick) = 0;
};