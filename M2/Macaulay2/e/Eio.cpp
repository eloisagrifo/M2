// Copyright 1998 by Michael E. Stillman


// This file contains the text and binary I/O routines.  This is done
// to keep the I/O stream use localized to one file, and to keep the
// magic numbers used also restricted to one file.

//#include <iostream.h>
#include "Eio.hpp"
#include "EZZp.hpp"
#include "Emonorder.hpp"
#include "Emonoid.hpp"
#include "Ering.hpp"
#include "Efreemod.hpp"
#include "Evector.hpp"
#include "Eringmap.hpp"

#include "bin_io.hpp"

extern int p_one;
extern int p_parens;
extern int p_plus;

#if 0
static void bin_int_in(istream &i, int &a)
{
  i >> a;
}

static bool get_magic_number(istream &i, int magic)
{
  int a;
  bin_int_in(i,a);
  return a == magic;
}
#endif
/////////////////////
// EZZ //////////////
/////////////////////

void EZZ::text_out(buffer &o) const
{
  o << "ZZ";
}

void EZZ::bin_out(buffer &o) const
{
  bin_int_out(o, MAGIC_ZZ);
}
#if 0
EZZ *EZZ::binary_in(istream &i)
{
  if (!get_magic_number(i,MAGIC_ZZ))
    return 0;
  return new EZZ();
}
#endif
/////////////////////
// EZZ elements /////
/////////////////////

void EZZ::elem_text_out(buffer &o, ZZ a) const
{
  // This depends on whether we need to print a "+", a "1".
#if 0
  bool is_neg = (a < 0);
  bool is_one = (a == 1 || a = -1);

  if (!is_neg && p_plus) o << "+";
  if (isone)
    {
      if (is_neg) o << "-";
      if (p_one) o << "1";
    }
  else
    o << a;
#endif

  if (a < 0) 
    {
      o << '-';
      a = -a;
    }
  else if (p_plus) 
    o << '+';
  if (p_one || a != 1) o << a;
}

void EZZ::elem_bin_out(buffer &o, ZZ a) const
{
  bin_int_out(o, a);  // CHANGE WHEN element can be infinite precision
}

#if 0
ZZ EZZ::elem_binary_in(istream &i) const
{
  int a;
  bin_int_in(i,a);
  return _from_int(a);
}
#endif
/////////////////////
// EZZp /////////////
/////////////////////

void EZZp::text_out(buffer &o) const
{
  o << "ZZ/" << P;
}

void EZZp::bin_out(buffer &o) const
{
  bin_int_out(o, MAGIC_ZZP);
  bin_int_out(o, P);
}
#if 0
EZZp *EZZp::binary_in(istream &i)
{
  int p;
  if (!get_magic_number(i,MAGIC_ZZP))
    return 0;
  bin_int_in(i, p);
  // CHECK: that p is a proper value (perhaps also check that it is prime?)
  return EZZp::make(p);
}
#endif
/////////////////////
// EZZp elements /////
/////////////////////

void EZZp::elem_text_out(buffer &o, int a) const
{
  // This depends on whether we need to print a "+", a "1", and whether to lift the
  // value to characteristic zero type number, if possible.
  // MES: WHAT ABOUT LIFTING TO CHAR 0??
  if (a > P/2) a -= P;
  if (a < 0) 
    {
      o << '-';
      a = -a;
    }
  else if (p_plus) 
    o << '+';
  if (p_one || a != 1) o << a;

}

void EZZp::elem_bin_out(buffer &o, int a) const
{
  if (a > P/2) a -= P;
  bin_int_out(o, a);
}
#if 0
int EZZp::elem_binary_in(istream &i) const
{
  int a;
  bin_int_in(i,a);
  return _from_int(a);
}
#endif
/////////////////////
// Monomial orders //
/////////////////////
#if 0
static bool check_mon_order(const int *moncodes)
{
  int j, m;
  if (*moncodes++ != MAGIC_MONORDER) return false;
  int len = *moncodes++;
  if (len < 5) return false; // MAGIC_MONORDER, len, nvars, nblocks, MAGIC_MONORDER_END
  int nvars = *moncodes++;
  if (nvars < 0) return false;
  int nblocks = *moncodes++;
  if (nblocks < 0) return false;
  len -= 4;

  int total_nvars = nvars;
  for (int i = nblocks-1; i >= 0; i--)
    {
      int ty = *moncodes++;
      switch (ty)
	{
	case MO_LEX:
	case MO_REVLEX:
	  len -= 3;
	  if (len <= 0) return false;
	  m = *moncodes++;
	  moncodes++;
	  total_nvars -= m;
	  if (m <= 0) return false;
	  break;

	case MO_NC_LEX:
	  len -= 2;
	  if (len <= 0) return false;
	  m = *moncodes++;
	  total_nvars -= m;
	  if (m <= 0) return false;
	  break;

	case MO_WTFCN:
	  len -= nvars+1;
	  if (len <= 0) return false;
	  moncodes += nvars;
	  break;

	case MO_WTREVLEX:
	  m = *moncodes++;
	  total_nvars -= m;
	  if (m <= 0) return false;
	  moncodes++;  // isgroup flag
	  len--;
	  len -= m+2;
	  if (len <= 0) return false;
	  for (j=0; j<m; j++)
	    if (*moncodes++ <= 0) return false;
	  break;
	}
    }

  if (len != 1) return false;
  if (*moncodes != MAGIC_MONORDER_END) return false;
  if (total_nvars != 0) return false;
  return true;
}
#endif
EMonomialOrder *EMonomialOrder::get_binary(const int *moncodes)
{
  int m,i,j;
  int *wts;
  bool isgroup;
  moncodes++;			// get past MAGIC_MONORDER
  moncodes++;			// get past length
  int nvars = *moncodes++;
  int nblocks = *moncodes++;
  EMonomialOrder *result = make();
  for (i = nblocks-1; i >= 0; i--)
    {
      int typ = *moncodes++;
      switch (typ)
	{
	case MO_LEX:
	  m = *moncodes++;
	  isgroup = (bool) *moncodes++;
	  result->lex(m,isgroup);	// Append a lex block
	  break;

	case MO_REVLEX:
	  m = *moncodes++;
	  isgroup = (bool) *moncodes++;
	  result->revlex(m,isgroup);
	  break;

	case MO_NC_LEX:
	  m = *moncodes++;
	  result->NClex(m);	// Append a lex block
	  break;

	case MO_WTFCN:
	  wts = new int[nvars];
	  for (j=0; j<nvars; j++)
	    wts[j] = *moncodes++;
	  result->weightFunction(nvars, wts);
	  delete [] wts;
	  break;

	case MO_WTREVLEX:
	  m = *moncodes++;
	  isgroup = (bool) *moncodes++;
	  wts = new int[m];
	  for (j=0; j<m; j++)
	    wts[j] = *moncodes++;
	  result->revlexWeights(m,wts,isgroup);
	  break;
	}
    }
  return result;
}

void EMonomialOrder::text_out(buffer &o) const
{
  int j;
  o << "EMonomialOrder[";

  for (int i=0; i<nblocks; i++)
    {
      mon_order_node *b = order[i];
      if (i >= 1) o << ",";
      if (b->first_slot == componentloc)
	o << "c,";
      switch (b->typ)
	{
	case MO_LEX:
	  if (b->isgroup)
	    o << "grouplex(" << b->n << ")";
	  else 
	    o << "lex(" << b->n << ")";
	  break;

	case MO_REVLEX:
	  if (b->isgroup)
	    o << "grouprevlex(" << b->n << ")";
	  else
	    o << "revlex(" << b->n << ")";
	  break;
	  
	case MO_NC_LEX:
	  o << "NClex(" << b->n << ")";
	  break;

	case MO_WTFCN:
	  o << "wt(";
	  for (j=0; j<b->nweights; j++)
	    {
	      if (j > 0) o << " ";
	      o << b->weights[j];
	    }
	  o << ")";
	  break;

	case MO_WTREVLEX:
	  if (b->isgroup)
	    o << "groupwtrevlex(";
	  else
	    o << "wtrevlex(";
	  for (j=0; j<b->nweights; j++)
	    {
	      if (j > 0) o << " ";
	      o << b->weights[j];
	    }
	  o << ")";
	  break;
	}
    }
  if (componentloc == nslots)
    o << ",c";
  o << "]";
}

int *EMonomialOrder::put_binary() const
{
  // MESXX
  return 0;
}

void EMonomialOrder::bin_out(buffer &o) const
{
  int *moncodes = put_binary();
  if (moncodes == 0) return;  // WRITE put_binary()
  int len = moncodes[1];
  for (int i=0; i<len; i++)
    bin_int_out(o, moncodes[i]);
  delete [] moncodes;
}
#if 0
EMonomialOrder *EMonomialOrder::binary_in(istream &i)
{
  int len;
  if (!get_magic_number(i, MAGIC_MONORDER))
    return 0;
  bin_int_in(i, len);
  int *moncodes = new int[len];
  moncodes[0] = MAGIC_MONORDER;
  moncodes[1] = len;
  for (int j=2; j<len; j++)
    bin_int_in(i, moncodes[j]);
  if (!check_mon_order(moncodes))
    {
      delete [] moncodes;
      return 0;
    }
  EMonomialOrder *result = get_binary(moncodes);
  delete [] moncodes;
  return result;
}
#endif
////////////////////////
// Commutative monoid //
////////////////////////

void ECommMonoid::text_out(buffer &o) const
{
  o << "[";
  for (int i=0; i<nvars; i++)
    {
      o << getVariableName(i) << ",";
    }
  monorder->text_out(o);
  o << "]";
}

void ECommMonoid::bin_out(buffer &) const
{
  // MES: write
}
#if 0
ECommMonoid *ECommMonoid::binary_in(istream &i)
{
  // MES: write
  if (!get_magic_number(i,MAGIC_MONOID))
    return 0;
  return 0;
}
#endif
///////////////////////////
// NonCommutative monoid //
///////////////////////////

void ENCMonoid::text_out(buffer &o) const
{
  o << "<<";
  for (int i=0; i<nvars; i++)
    {
      o << getVariableName(i) << ",";
    }
  monorder->text_out(o);
  o << ">>";
}

void ENCMonoid::bin_out(buffer &) const
{
  // MES: write
}

#if 0
ENCMonoid *ENCMonoid::binary_in(istream &i)
{
  // MES: write
  if (!get_magic_number(i,MAGIC_MONOID))
    return 0;
  return 0;
}
#endif
/////////////////////////////
// (Commutative) monomials //
/////////////////////////////

void ECommMonoid::elem_text_out(buffer &o, const monomial *a) const
{
  int len = 0;
  const int *exp = to_exponents(a);;
  for (int pv=0; pv<nvars; pv++)
    {
      int v = print_order[pv];
      if (exp[v] != 0) {
	len++;
	o << var_names[v];
	int e = exp[v];
	int single = (var_names[v][1] == '\0');
	if (e > 1 && single) o << e;
	else if (e > 1) o << "^" << e;
	else if (e < 0) o << "^(" << e << ")";	
      }
    }
  if (len == 0 && p_one) o << "1";
}

void ECommMonoid::elem_bin_out(buffer &o, const monomial *a) const
{
  intarray vp;
  to_variable_exponent_pairs(a, vp);
  bin_int_out(o, vp.length()/2);
  for (int i=0; i<vp.length(); i++)
    bin_int_out(o, vp[i]);
}
#if 0
const monomial *ECommMonoid::elem_binary_in(istream &i) const
{
  int j, len, v, e;
  intarray vp;
  bin_int_in(i, len);
  for (j=0; j<len; j++)
    {
      bin_int_in(i, v);
      bin_int_in(i, e);
      vp.append(v);
      vp.append(e);
    }
  return monomial_from_variable_exponent_pairs(vp);
}
#endif
/////////////////////////////////
// (Non-Commutative) monomials //
/////////////////////////////////

void ENCMonoid::elem_text_out(buffer &o, const monomial *a) const
{
  intarray vp;
  to_variable_exponent_pairs(a, vp);
  int len = vp.length();
  for (int i=0; i<len; i+=2)
    {
      int v = vp[i];
      int e = vp[i+1];
      int single = (var_names[v][1] == '\0');
      o << var_names[v];
      if (e > 1 && single) o << e;
      else if (e > 1) o << "^" << e;
      else if (e < 0) o << "^(" << e << ")";	
    }
  if (len == 0 && p_one) o << "1";
}

void ENCMonoid::elem_bin_out(buffer &o, const monomial *a) const
{
  intarray vp;
  to_variable_exponent_pairs(a, vp);
  bin_int_out(o, vp.length()/2);
  for (int i=0; i<vp.length(); i++)
    bin_int_out(o, vp[i]);
}
#if 0
const monomial *ENCMonoid::elem_binary_in(istream &i) const
{
  int j, len, v, e;
  intarray vp;
  bin_int_in(i, len);
  for (j=0; j<len; j++)
    {
      bin_int_in(i, v);
      bin_int_in(i, e);
      vp.append(v);
      vp.append(e);
    }
  return monomial_from_variable_exponent_pairs(vp);
}
#endif
//////////////////////
// Polynomial rings //
//////////////////////
 
void ECommPolynomialRing::text_out(buffer &o) const
{
  K->text_out(o);
  M->text_out(o);
}

void ECommPolynomialRing::bin_out(buffer &o) const
{
  bin_int_out(o, MAGIC_POLYRING);
  K->bin_out(o);
  M->bin_out(o);
}

#if 0
ECommPolynomialRing *ECommPolynomialRing::binary_in(istream &i)
{
#if 0
  if (!get_magic_number(i,MAGIC_POLYRING))
    return 0;
  EZZp *K = EZZp::binary_in(i);
  if (K == 0) return 0;
  ECommMonoid *M = ECommMonoid::binary_in(i);
  if (M == 0)
    {
      //MES: K->bump_down();
      return 0;
    }
  return new ECommPolynomialRing(K,M);
#endif
  return 0;
}
#endif
//////////////////////
// EWeylAlgebra ///////
//////////////////////
 
void EWeylAlgebra::text_out(buffer &o) const
{
  o << "EWeylAlgebra(";
  K->text_out(o);
  M->text_out(o);
  o << ",WeylPairing=>(";
  for (int i=0; i<nderivatives; i++) {
    if (i > 0) o << ",";
    o << M->getVariableName(derivative[i]) << "=>" 
      << M->getVariableName(commutative[i]);
  }
  o << "))";
}

void EWeylAlgebra::bin_out(buffer &o) const
{
  bin_int_out(o, MAGIC_POLYRING);
  K->bin_out(o);
  M->bin_out(o);
}

#if 0
EWeylAlgebra *EWeylAlgebra::binary_in(istream &i)
{
#if 0
  if (!get_magic_number(i,MAGIC_POLYRING))
    return 0;
  EZZp *K = EZZp::binary_in(i);
  if (K == 0) return 0;
  ECommMonoid *M = ECommMonoid::binary_in(i);
  if (M == 0)
    {
      //MES: K->bump_down();
      return 0;
    }
  return EWeylAlgebra::make(K,M,0,0,0);
#endif
  return 0;
}
#endif
///////////////////////////////////
// ESkewCommPolynomialRing //
///////////////////////////////////
 
void ESkewCommPolynomialRing::text_out(buffer &o) const
{
  o << "SkewCommutative(";
  K->text_out(o);
  M->text_out(o);
  o << ",SkewVariables=>(";
  for (int i=0; i<nskew; i++) {
    if (i > 0) o << ",";
    o << M->getVariableName(skewlist[i]);
  }
  o << "))";
}

//////////////////////
// ENCPolynomialRing //
//////////////////////
 
void ENCPolynomialRing::text_out(buffer &o) const
{
  K->text_out(o);
  M->text_out(o);
}

//////////////////////
// Polynomials ////////
//////////////////////

void EPolynomialRing::elem_text_out(buffer &o, const epoly *f) const
{
  if (f == 0)
    {
      o << "0";
      return;
    }

  const EMonoid *M = getMonoid();
  const ERing *K = getCoefficientRing();
  int old_one = p_one;
  int old_parens = p_parens;
  int old_plus = p_plus;

  bool two_terms = (f->next != 0);
  bool needs_parens = p_parens && two_terms;

  if (needs_parens) 
    {
      if (old_plus) o << '+';
      o << '(';
      p_plus = 0;
    }

  for (const epoly *t = f; t != 0; t = t->next)
    {
      int isone = M->is_one(t->monom);
      p_parens = !isone;
      p_one = (isone && needs_parens) || (isone && old_one);
      K->elem_text_out(o,t->coeff);
      if (!isone)
	M->elem_text_out(o, t->monom);
      p_plus = 1;
    }
  if (needs_parens) o << ')';

  p_one = old_one;
  p_parens = old_parens;
  p_plus = old_plus;
}

void EPolynomialRing::elem_bin_out(buffer &o, const epoly *f) const
{
  const EMonoid *M = getMonoid();
  bin_int_out(o,n_terms(f));

  for (const epoly *t=f; t != 0; t = t->next)
    {
      M->elem_bin_out(o, t->monom);
      K->elem_bin_out(o, t->coeff);
    }
}

void EFreeModule::text_out(buffer &o) const
{
  const EPolynomialRing *A = R->toPolynomialRing();
  o << "EFreeModule(",
  R->text_out(o);
  o << ",rank = ";
  o << rank();
  o << ",degrees = ";
  for (int i=0; i<rank(); i++)
    {
      getDegreeMonoid()->elem_text_out(o, _degrees[i]);
      if (hasInducedOrder())
        {
          o << ".";
          A->getMonoid()->elem_text_out(o, _orderings[i]);
          o << ".";
          o << _tiebreaks[i];
        }
      o << " ";
    }
}

void EFreeModule::bin_out(buffer &o) const
{
  const EMonoid *D = getDegreeMonoid();
  bin_int_out(o, D->n_vars() * rank());
  for (int i=0; i<rank(); i++)
    {
      const int *exp = D->to_exponents(getDegree(i));
      for (int j=0; j < D->n_vars(); j++)
	bin_int_out(o, exp[j]);
    }
}

void EVector::text_out(buffer &o) const
{
  F->getRing()->vec_text_out(o, *this);
}
void EVector::bin_out(buffer &o) const
{
  F->getRing()->vec_bin_out(o, *this);
}
void ERing::vec_text_out(buffer &o, const EVector &v) const
{
  if (v.len == 0)
    {
      o << "0";
      return;
    }

  int old_one = p_one;
  int old_parens = p_parens;
  int old_plus = p_plus;
  
  for (EVector::iterator t = v; t.valid(); ++t)
    {
      p_one = false;
      K->elem_text_out(o,t->coeff);
      o << "<" << t->component << ">";
      p_plus = 1;
    }

  p_one = old_one;
  p_parens = old_parens;
  p_plus = old_plus;
}
void EPolynomialRing::vec_text_out(buffer &o, const EVector &v) const
{
  if (v.len == 0)
    {
      o << "0";
      return;
    }

  const EMonoid *M = getMonoid();

  int old_one = p_one;
  int old_parens = p_parens;
  int old_plus = p_plus;
  
  for (EVector::iterator t = v; t.valid(); ++t)
    {
      int isone = M->is_one(t->monom);
      p_one = false;
      K->elem_text_out(o,t->coeff);
      if (!isone)
	M->elem_text_out(o, t->monom);
      o << "<" << t->component << ">";
      p_plus = 1;
    }

  p_one = old_one;
  p_parens = old_parens;
  p_plus = old_plus;
}

void ERing::vec_bin_out(buffer &o, const EVector &v) const
{
  bin_int_out(o,v.len);

  for (EVector::iterator t = v; t.valid(); ++t)
    {
      bin_int_out(o, t->component);
      K->elem_bin_out(o, t->coeff);
    }
}
void EPolynomialRing::vec_bin_out(buffer &o, const EVector &v) const
{
  bin_int_out(o,v.len);

  for (EVector::iterator t = v; t.valid(); ++t)
    {
      bin_int_out(o, t->component);
      getMonoid()->elem_bin_out(o, t->monom);
      K->elem_bin_out(o, t->coeff);
    }
}
///////////////
// Ring maps //
///////////////
void ERingMap::bin_out(buffer &o) const
{
  bin_int_out(o, nvars);
  for (int i=0; i<nvars; i++)
    R->elem_text_out(o, _elem[i].bigelem);
}

void ERingMap::text_out(buffer &o) const
{
  o << "(";
  for (int i=0; i<nvars; i++)
    {
      if (i > 0) o << ", ";
      R->elem_text_out(o, _elem[i].bigelem);
    }
  o << ")";
}


#if 0

vector EFreeModule::elem_binary_in(istream &i) const
{
  // MES: sort these terms, so that we don't need to insist that the input is
  // in the correct order??
  poly head;
  poly *result = &head;
  int len;
  bin_int_in(i, len);
  for (int j=0; j<len; j++)
    {
      // Read a term: a term is in the form (coeff,monomial)
      poly *p = R->new_term();
      bin_int_in(i,p->component);
      p->coeff = K->elem_binary_in(i);
      p->monom = M->elem_binary_in(i);
      result->next = p;
      result = p;
    }
  result->next = 0;
  vector G;
  G.len = len;
  G.elems = head.next;
  return G;
}

#endif

