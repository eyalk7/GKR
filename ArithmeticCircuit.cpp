#include "ArithmeticCircuit.h"

using namespace std;

int ArithmeticCircuit::addGate(GateType type, int layer, int in1, int in2) {
  int newGateLabel = gates.size();

  if (type == INPUT) {
    if (layer != 0 || in1 != -1 || in2 != -1) {
      throw invalid_argument(
          "Given INPUT gate type but layer is not 0 or in gates are not -1.");
    }
  }

  auto inGate1 = gates.find(in1);
  auto inGate2 = gates.find(in2);

  if (inGate1 == gates.end() || inGate2 == gates.end()) {
    throw invalid_argument("Given in gates don't exist.");
  }

  if (inGate1->second.layer != inGate2->second.layer ||
      inGate1->second.layer != layer - 1) {
    throw invalid_argument("Given in gates are not in the same layer or not in "
                           "the layer below the new gate.");
  }

  gates[newGateLabel] = {type, layer, in1, in2};
  layers[layer].insert(newGateLabel);

  return newGateLabel;
}

void ArithmeticCircuit::assignValueToInputGate(int gateLabel, int val) {
  auto gate = gates.find(gateLabel);
  if (gate == gates.end()) {
    throw invalid_argument("Gate doesn't exist.");
  }
  if (gate->second.type != INPUT) {
    throw invalid_argument("Given gate is not an input gate.");
  }

  gate->second.val = val;
}

void ArithmeticCircuit::runCircuit() {
  for (int layer = 1; layer < layers.size(); layer++) {
    for (int label : layers.at(layer)) {
      Gate &gate = gates.at(label);
      int inGate1Val = gates.at(gate.in1).val;
      int inGate2Val = gates.at(gate.in2).val;

      switch (gate.type) {
      case ADDITION:
        gate.val = inGate1Val + inGate2Val;
        break;
      case MULTIPLICATION:
        gate.val = inGate1Val * inGate2Val;
        break;
      default:
        throw runtime_error("Unexpected error.");
        break;
      }
    }
  }
}