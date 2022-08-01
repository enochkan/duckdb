#include "duckdb/planner/operator/logical_distinct.hpp"

#include "duckdb/common/string_util.hpp"

namespace duckdb {

string LogicalDistinct::ParamsToString() const {
	string result = LogicalOperator::ParamsToString();
	if (!distinct_targets.empty()) {
		result += StringUtil::Join(distinct_targets, distinct_targets.size(), "\n",
		                           [](const unique_ptr<Expression> &child) { return child->GetName(); });
	}

	return result;
}
void LogicalDistinct::Serialize(FieldWriter &writer) const {
	writer.WriteSerializableList(distinct_targets);
}

unique_ptr<LogicalOperator> LogicalDistinct::Deserialize(ClientContext &context, LogicalOperatorType type,
                                                         FieldReader &reader) {
	auto distinct_targets = reader.ReadRequiredSerializableList<Expression>(context);
	return make_unique<LogicalDistinct>(move(distinct_targets));
}

} // namespace duckdb
