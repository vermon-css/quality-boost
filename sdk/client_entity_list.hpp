#pragma once

class BaseHandle;
class IClientNetworkable;
class IClientUnknown;
class IClientEntity;

class IClientEntityList {
public:
    virtual IClientNetworkable* get_client_networkable(int ent_num) = 0;
    virtual IClientNetworkable* get_client_networkable_from_hande(BaseHandle ent) = 0;
    virtual IClientUnknown* get_client_unknown_from_handle(BaseHandle ent) = 0;
    virtual IClientEntity* get_client_entity(int ent_num) = 0;
    virtual IClientEntity* get_client_entity_from_handle(BaseHandle ent) = 0;
    virtual int number_of_entities(bool include_non_networkable) = 0;
    virtual int get_highest_entity_index() = 0;
    virtual void set_max_entities(int n) = 0;
    virtual int get_max_entities() = 0;
};
