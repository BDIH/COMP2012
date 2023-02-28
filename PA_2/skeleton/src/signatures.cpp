#include "signatures.h"
#include "number.h"

SigType Signature::GetType() const
{
    string name = typeid(*this).name();

    if (name == "12DSASignature")
        return DSA;
    else if (name == "16SchnorrSignature")
        return Schnorr;
    else
        throw invalid_argument("Signature Type does not exist!");
}

//Todo: Constructors/Destructors
//Signature Part
Signature::Signature() {};

Signature::~Signature() {};

SchnorrSignature::SchnorrSignature(const Number* s, const Number* e) : Signature(), s(s), e(e){}

SchnorrSignature::~SchnorrSignature(){ delete s; delete e; cout<< "Destruct SchnorrSignature..." <<endl;}

DSASignature::DSASignature(const Number* r, const Number* s) : Signature(), r(r), s(s) {}

DSASignature::~DSASignature(){ delete r; delete s; cout<< "Destruct DSASignature..." <<endl;}

//Public Key Part
SchnorrPublicKey::~SchnorrPublicKey(){ delete y; cout<< "Destruct SchnorrPublicKey..." <<endl;}

DSAPublicKey::DSAPublicKey(const Number* y) : y(y) {}

DSAPublicKey::~DSAPublicKey(){ delete y; cout<< "Destruct DSAPublicKey..." <<endl;}

//Secret Key Part
SchnorrSecretKey::SchnorrSecretKey(const Number* x) : x(x) {}

SchnorrSecretKey::~SchnorrSecretKey(){ delete x; cout<< "Destruct SchnorrSecretKey..." <<endl;}

DSASecretKey::~DSASecretKey(){ delete x; cout<<"Destruct DSASecretKey..."<<endl;}

bool SchnorrPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo
    const SchnorrSignature* temp = dynamic_cast<const SchnorrSignature*>(&signature);
    const Number* temp_s = temp->s;
    const Number* temp_e = temp->e;
    Number temp_one = Number(1);
    if((Number::NSign(Number::Sub(*temp_s, temp_one))) >= 0 
        && (Number::NSign(Number::Sub(*temp_e, temp_one))) >= 0 
        && Number::NSign(Number::Sub(Number::Sub(*Number::Q, temp_one), *temp_s))>= 0 
        && Number::NSign(Number::Sub(Number::Sub(*Number::Q, temp_one), *temp_e))>= 0){
        Number r_v = Number::Mul_Mod(Number::Pow(*Number::G,*temp_s,*Number::P), Number::Pow(*(this->y),*temp_e,*Number::P), *Number::P);
        Number e_v = Number::Mod(Number::Hash(r_v, message), *Number::Q);

        if((Number::NSign(Number::Sub(e_v, *temp_e))) == 0){
            return true;
        }

        else{
            return false;  
        }
    }

    else{
        return false;
    }
}

bool DSAPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo
    const DSASignature* temp = dynamic_cast<const DSASignature*>(&signature);
    const Number* temp_r = temp->r;
    const Number* temp_s = temp->s;
    Number temp_one = Number(1);
    if((Number::NSign(Number::Sub(*temp_r, temp_one))) >= 0 
        && (Number::NSign(Number::Sub(*temp_s, temp_one))) >= 0
        && Number::NSign(Number::Sub(Number::Sub(*Number::Q, temp_one), *temp_r))>= 0 
        && Number::NSign(Number::Sub(Number::Sub(*Number::Q, temp_one), *temp_s))>= 0){
        
        Number w = Number::Inv(*temp_s, *Number::Q);
        Number z = Number::Hash(message);
        Number u1 = Number::Mul_Mod(z, w, *Number::Q);
        Number u2 = Number::Mul_Mod(*temp_r, w, *Number::Q);

        Number compare =  Number::Mod(Number::Mul_Mod(Number::Pow(*Number::G, u1,*Number::P), Number::Pow(*(this->y), u2,*Number::P), *Number::P), *Number::Q);

        if(Number::NSign(Number::Sub(compare, *temp_r)) == 0){
            return true;
        }

        else{
            return false;  
        }
    }

    else{
        return false;
    }
}

const Signature *SchnorrSecretKey::Sign(const string &message) const
{
    //Todo
    while (true)
    {
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Pow(*Number::G, k, *Number::P);
        Number e = Number::Mod(Number::Hash(r, message),*Number::Q);
        Number s = Number::Mod(Number::Sub(k, Number::Mul_Mod(*(this->x), e, *Number::Q)), *Number::Q);

        if (Number::NSign(s) > 0 && Number::NSign(e) > 0)
            return new SchnorrSignature(new Number(s), new Number(e));   
    }
}



const Signature *DSASecretKey::Sign(const string &message) const
{
    while (true)
    {
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Mod(Number::Pow(*Number::G, k, *Number::P), *Number::Q);
        Number z = Number::Hash(message);
        Number zxr = Number::Mod(Number::Add(z, Number::Mul_Mod(*(this->x), r, *Number::Q)), *Number::Q);
        Number ki = Number::Inv(k, *Number::Q);
        Number s = Number::Mul_Mod(ki, zxr, *Number::Q);
    
        if (Number::NSign(r) > 0 && Number::NSign(s) > 0)
            return new DSASignature(new Number(r), new Number(s));
    }
}

SigPair::SigPair(const PublicKey *publicKey, const SecretKey *secretKey)
    : publicKey(publicKey), secretKey(secretKey)
{
}

SigPair::~SigPair()
{
    cout << "Destruct SigPair..."<<endl;
    delete publicKey;
    delete secretKey;
}

const SigPair *GenerateKey(SigType sigType, const string &info)
{
    if (sigType == DSA )
    {
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);

        DSASecretKey *sk = new DSASecretKey(newX);
        DSAPublicKey *pk = new DSAPublicKey(newY);

        SigPair *sigPair = new SigPair(pk, sk);

        return sigPair;
    }
    else if (sigType == Schnorr )
    {
        //Todo
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);

        SchnorrSecretKey *sk = new SchnorrSecretKey(newX);
        SchnorrPublicKey *pk = new SchnorrPublicKey(newY);

        SigPair *sigPair = new SigPair(pk, sk);
        
        return sigPair;
    }
    
    return nullptr;
}

vector<SigType> SigTypes()
{
    vector<SigType> s;
    s.push_back(DSA);
    s.push_back(Schnorr);
    return s;
}
