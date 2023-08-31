#include <map>
#include <set>

enum GateType { INPUT, ADDITION, MULTIPLICATION };

class ArithmeticCircuit {
public:
  ArithmeticCircuit() = default;

  /// @brief Add a gate to the circuit.
  /// @param type Gate type.
  /// @param layer The Layer of the gate.
  /// @param in1 The first input gate of the new gate (for non-input gates).
  /// @param in2 The second input gate of the new gate (for non input gates).
  /// @returns The new gate's label.
  int addGate(GateType type, int layer, int in1 = -1, int in2 = -1);

  /// @brief Assigns value to an input gate (default value in every input gate
  /// is 0).
  /// @param gateLabel The label of the gate to assign value to.
  /// @param val The value.
  void assignValueToInputGate(int gateLabel, int val);

  /// @brief Runs the circuit. I.e., fills the value in all gates, propagated
  /// from the input gates.
  void runCircuit();

private:
  struct Gate {
    /// @brief Gate type.
    GateType type = INPUT;

    /// @brief Gate layer.
    int layer = 0;

    /// @brief Input gates.
    int in1 = -1, in2 = -1;

    /// @brief Value (after circuit run, or after assignment for input gates);
    int val = 0;
  };

  /// @brief A mapping from gate label to the gate metadata.
  std::map<int, Gate> gates;

  /// @brief A mapping from layer index to the gates labels of this layer.
  std::map<int, std::set<int>> layers;
};