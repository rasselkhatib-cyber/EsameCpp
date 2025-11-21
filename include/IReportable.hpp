#ifndef IREPORTABLE_HPP
#define IREPORTABLE_HPP

class IReportable {
public:
    virtual void mostraDettagli() const = 0;

    virtual ~IReportable() = default;
};
#endif 
//INTERFACCIA VIRTUALE                                    
