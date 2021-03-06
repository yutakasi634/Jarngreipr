#ifndef JARNGREIPR_MODEL_CG_CHAIN_H
#define JARNGREIPR_MODEL_CG_CHAIN_H
#include <jarngreipr/model/CGBead.hpp>
#include <vector>
#include <memory>

namespace jarngreipr
{

template<typename realT>
class CGChain
{
  public:
    using real_type = realT;
    using bead_type = CGBead<real_type>;
    using bead_ptr  = std::shared_ptr<bead_type>;
    using container_type = std::vector<bead_ptr>;
    using iterator       = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

  public:

    CGChain(const std::string& name): name_(name){}

    CGChain(const CGChain&) = default;
    CGChain(CGChain&&)      = default;
    CGChain& operator=(const CGChain&) = default;
    CGChain& operator=(CGChain&&)      = default;
    ~CGChain() = default;

    bool       empty() const noexcept {return beads_.empty();}
    std::size_t size() const noexcept {return beads_.size();}

    void push_back(const std::shared_ptr<bead_type>& b)
    {beads_.push_back(b);}
    void push_back(std::shared_ptr<bead_type>&& b)
    {beads_.push_back(std::move(b));}

    template<typename ... Ts>
    void emplace_back(Ts&& ... ts)
    {beads_.emplace_back(std::forward<Ts>(ts)...);}

    bead_ptr&       operator[](const std::size_t i)       noexcept {return beads_[i];}
    bead_ptr const& operator[](const std::size_t i) const noexcept {return beads_[i];}
    bead_ptr&       at(const std::size_t i)       {return beads_.at(i);}
    bead_ptr const& at(const std::size_t i) const {return beads_.at(i);}

    iterator       begin()        noexcept {return beads_.begin();}
    iterator       end()          noexcept {return beads_.end();}
    const_iterator begin()  const noexcept {return beads_.begin();}
    const_iterator end()    const noexcept {return beads_.end();}
    const_iterator cbegin() const noexcept {return beads_.cbegin();}
    const_iterator cend()   const noexcept {return beads_.cend();}

    bead_ptr&       front()       noexcept {return beads_.front();}
    bead_ptr const& front() const noexcept {return beads_.front();}
    bead_ptr&       back()        noexcept {return beads_.back();}
    bead_ptr const& back()  const noexcept {return beads_.back();}

    container_type const& beads() const noexcept {return beads_;}
    container_type&       beads()       noexcept {return beads_;}
    std::string const&    name()  const noexcept {return name_;}
    std::string&          name()        noexcept {return name_;}

  protected:

    std::string    name_;
    container_type beads_;
};

}//jarngreipr
#endif // JARNGREIPR_MODEL_CG_CHAIN_H
