#include "asn1fix_internal.h"

/*
 * Dereference DefinedValues:
 */
int
asn1f_fix_dereference_values(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	int r_value = 0;

	if(expr->value && expr->meta_type == AMT_VALUE) {
		if(asn1f_value_resolve(arg, expr)) {
			/* This function will emit messages */
			r_value = -1;
		}
	}

	return r_value;
}


/*
 * Dereference DEFAULT values
 */
int
asn1f_fix_dereference_defaults(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	int r_value = 0;

	if(expr->marker.default_value) {
		arg_t tmparg = *arg;
		asn1p_expr_t tmpexpr = *expr;

		switch(expr->marker.default_value->type) {
		default:
			return r_value;
		case ATV_REFERENCED:
			break;
		}

		tmparg.expr = &tmpexpr;
		tmpexpr.meta_type = AMT_VALUE;
		tmpexpr.marker.default_value = 0;
		tmpexpr.value = expr->marker.default_value;
		if(asn1f_value_resolve(&tmparg, &tmpexpr))
			r_value = -1;
		expr->marker.default_value = tmpexpr.value;
	}

	return r_value;
}

