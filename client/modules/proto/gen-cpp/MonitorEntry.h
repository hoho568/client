/**
 * Autogenerated by Thrift Compiler (0.8.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MonitorEntry_H
#define MonitorEntry_H

#include <TProcessor.h>
#include "monitor_entry_types.h"

namespace infra { namespace monitor {

class MonitorEntryIf {
 public:
  virtual ~MonitorEntryIf() {}
  virtual void GetServiceEntry(ServiceEntry& _return, const std::string& host_name) = 0;
};

class MonitorEntryIfFactory {
 public:
  typedef MonitorEntryIf Handler;

  virtual ~MonitorEntryIfFactory() {}

  virtual MonitorEntryIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(MonitorEntryIf* /* handler */) = 0;
};

class MonitorEntryIfSingletonFactory : virtual public MonitorEntryIfFactory {
 public:
  MonitorEntryIfSingletonFactory(const boost::shared_ptr<MonitorEntryIf>& iface) : iface_(iface) {}
  virtual ~MonitorEntryIfSingletonFactory() {}

  virtual MonitorEntryIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(MonitorEntryIf* /* handler */) {}

 protected:
  boost::shared_ptr<MonitorEntryIf> iface_;
};

class MonitorEntryNull : virtual public MonitorEntryIf {
 public:
  virtual ~MonitorEntryNull() {}
  void GetServiceEntry(ServiceEntry& /* _return */, const std::string& /* host_name */) {
    return;
  }
};

typedef struct _MonitorEntry_GetServiceEntry_args__isset {
  _MonitorEntry_GetServiceEntry_args__isset() : host_name(false) {}
  bool host_name;
} _MonitorEntry_GetServiceEntry_args__isset;

class MonitorEntry_GetServiceEntry_args {
 public:

  MonitorEntry_GetServiceEntry_args() : host_name("") {
  }

  virtual ~MonitorEntry_GetServiceEntry_args() throw() {}

  std::string host_name;

  _MonitorEntry_GetServiceEntry_args__isset __isset;

  void __set_host_name(const std::string& val) {
    host_name = val;
  }

  bool operator == (const MonitorEntry_GetServiceEntry_args & rhs) const
  {
    if (!(host_name == rhs.host_name))
      return false;
    return true;
  }
  bool operator != (const MonitorEntry_GetServiceEntry_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MonitorEntry_GetServiceEntry_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MonitorEntry_GetServiceEntry_pargs {
 public:


  virtual ~MonitorEntry_GetServiceEntry_pargs() throw() {}

  const std::string* host_name;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MonitorEntry_GetServiceEntry_result__isset {
  _MonitorEntry_GetServiceEntry_result__isset() : success(false) {}
  bool success;
} _MonitorEntry_GetServiceEntry_result__isset;

class MonitorEntry_GetServiceEntry_result {
 public:

  MonitorEntry_GetServiceEntry_result() {
  }

  virtual ~MonitorEntry_GetServiceEntry_result() throw() {}

  ServiceEntry success;

  _MonitorEntry_GetServiceEntry_result__isset __isset;

  void __set_success(const ServiceEntry& val) {
    success = val;
  }

  bool operator == (const MonitorEntry_GetServiceEntry_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const MonitorEntry_GetServiceEntry_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MonitorEntry_GetServiceEntry_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MonitorEntry_GetServiceEntry_presult__isset {
  _MonitorEntry_GetServiceEntry_presult__isset() : success(false) {}
  bool success;
} _MonitorEntry_GetServiceEntry_presult__isset;

class MonitorEntry_GetServiceEntry_presult {
 public:


  virtual ~MonitorEntry_GetServiceEntry_presult() throw() {}

  ServiceEntry* success;

  _MonitorEntry_GetServiceEntry_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class MonitorEntryClient : virtual public MonitorEntryIf {
 public:
  MonitorEntryClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  MonitorEntryClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void GetServiceEntry(ServiceEntry& _return, const std::string& host_name);
  void send_GetServiceEntry(const std::string& host_name);
  void recv_GetServiceEntry(ServiceEntry& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class MonitorEntryProcessor : public ::apache::thrift::TProcessor {
 protected:
  boost::shared_ptr<MonitorEntryIf> iface_;
  virtual bool process_fn(apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, std::string& fname, int32_t seqid, void* callContext);
 private:
  std::map<std::string, void (MonitorEntryProcessor::*)(int32_t, apache::thrift::protocol::TProtocol*, apache::thrift::protocol::TProtocol*, void*)> processMap_;
  void process_GetServiceEntry(int32_t seqid, apache::thrift::protocol::TProtocol* iprot, apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  MonitorEntryProcessor(boost::shared_ptr<MonitorEntryIf> iface) :
    iface_(iface) {
    processMap_["GetServiceEntry"] = &MonitorEntryProcessor::process_GetServiceEntry;
  }

  virtual bool process(boost::shared_ptr<apache::thrift::protocol::TProtocol> piprot, boost::shared_ptr<apache::thrift::protocol::TProtocol> poprot, void* callContext);
  virtual ~MonitorEntryProcessor() {}
};

class MonitorEntryProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  MonitorEntryProcessorFactory(const ::boost::shared_ptr< MonitorEntryIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< MonitorEntryIfFactory > handlerFactory_;
};

class MonitorEntryMultiface : virtual public MonitorEntryIf {
 public:
  MonitorEntryMultiface(std::vector<boost::shared_ptr<MonitorEntryIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~MonitorEntryMultiface() {}
 protected:
  std::vector<boost::shared_ptr<MonitorEntryIf> > ifaces_;
  MonitorEntryMultiface() {}
  void add(boost::shared_ptr<MonitorEntryIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void GetServiceEntry(ServiceEntry& _return, const std::string& host_name) {
    size_t sz = ifaces_.size();
    for (size_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        ifaces_[i]->GetServiceEntry(_return, host_name);
        return;
      } else {
        ifaces_[i]->GetServiceEntry(_return, host_name);
      }
    }
  }

};

}} // namespace

#endif
