import "transaction.cats"

# cosignature attached to an aggregate transaction
struct CosignatureBody
	TRANSACTION_VERSION = make_const(uint8, 1)
	TRANSACTION_TYPE = make_const(TransactionType, MULTISIG_COSIGNATURE)

	# multisig transaction hash outer size
	multisig_transaction_hash_outer_size = make_reserved(uint32, 36)

	# [__value__] multisig transaction hash
	#
	# [size] multisig transaction hash size
	multisig_transaction_hash = inline SizePrefixedHash256

	# [__value__] multisig account address
	#
	# [size] multisig account address size
	multisig_account_address = inline SizePrefixedAddress

@is_size_implicit
struct Cosignature
	inline Transaction
	inline CosignatureBody

struct NonVerifiableCosignature
	inline NonVerifiableTransaction
	inline CosignatureBody

# cosignature attached to an aggregate transaction with prefixed size
struct SizePrefixedCosignature
	# cosignature size
	cosignature_size = sizeof(uint32, cosignature)

	# cosignature
	cosignature = Cosignature

# binary layout for a multisig transaction
struct MultisigTransactionBody
	TRANSACTION_VERSION = make_const(uint8, 1)
	TRANSACTION_TYPE = make_const(TransactionType, MULTISIG_TRANSACTION)

	# inner transaction size
	inner_transaction_size = sizeof(uint32, inner_transaction)

	# inner transaction
	inner_transaction = NonVerifiableTransaction

struct MultisigTransaction
	inline Transaction
	inline MultisigTransactionBody

	# number of attached cosignatures
	cosignatures_count = uint32

	# cosignatures
	cosignatures = array(SizePrefixedCosignature, cosignatures_count)

struct NonVerifiableMultisigTransaction
	inline NonVerifiableTransaction
	inline MultisigTransactionBody

