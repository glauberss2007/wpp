//
// Created by Alan de Freitas on 15/11/2017.
//

#ifndef WPP_USER_H
#define WPP_USER_H

#include <wpp/model.h>

namespace wpp {

    class user
            : public wpp::model {
        public:
            using self_t = model;

            ///////////////////////////////////////////////////////////////
            //            SPECIAL WAYS TO ATTRIBUTE TO FIELDS            //
            ///////////////////////////////////////////////////////////////

            self_t& set_password_attribute($value) {
                $this->attributes["password"] = bcrypt($value);
            }

            self_t& set_birthday_attribute($value) {
                $this->attributes["birthday"] = Carbon::createFromFormat("d/m/Y", $value)->toDateString();
            }

            ///////////////////////////////////////////////////////////////
            //                   SPECIAL FUNCTIONS                       //
            ///////////////////////////////////////////////////////////////

            self_t& is_unconfirmed() {
                return this->status == UserStatus::UNCONFIRMED;
            }


            self_t& is_active() {
                return this->status == UserStatus::ACTIVE;
            }


            self_t& is_banned() {
                return this->status == UserStatus::BANNED;
            }


            self_t& social_networks() {
                return this->hasOne(UserSocialNetworks, "user_id");
            }

            self_t& country() {
                return this->belongsTo(Country, "country_id");
            }

            self_t& activities() {
                return this->hasMany(Activity, "user_id");
            }

        protected:
            std::string _presenter;
            std::string _table = "auth_users";
            std::vector <std::string> _dates = {"last_login", "birthday"};
            std::vector <std::string> _fillable = {
                    "name", "email", "password", "username", "first_name", "last_name", "phone", "avatar",
                    "address", "country_id", "birthday", "last_login", "confirmation_token", "status",
                    "group_id", "remember_token", "nick", "last_sessid"
            };

            std::string _hidden = {"password", "remember_token"};

            self_t& mapper() {
                map("name",name);
                map("email",email);
                map("password",password);
                map("username",username);
                map("first_name",first_name);
                map("last_name",last_name);
                map("phone",phone);
                map("avatar",avatar);
                map("address",address);
                map("country_id",country_id);
                map("birthday",birthday);
                map("last_login",last_login);
                map("confirmation_token",confirmation_token);
                map("status",status);
                map("group_id",group_id);
                map("remember_token",remember_token);
                map("nick",nick);
                map("last_sessid",last_sessid);
            };

    };

}

//
//class can_reset_password {
//    public:
//        // Get the e-mail address where password reset links are sent.
//        function getEmailForPasswordReset() {
//            return $this->email;
//        }
//
//        // Send the password reset notification.
//        function sendPasswordResetNotification(token) {
//            $this->notify(new ResetPasswordNotification($token));
//        }
//};
//
//class authorizable {
//    public:
//        // Determine if the entity has a given ability.
//        bool can(string ability, vector <string> arguments) {
//            return app(Gate::
//            class)->forUser($this)->check($ability, $arguments);
//        }
//
//        // Determine if the entity does not have a given ability.
//        bool cant(string ability, vector <string> arguments = []) {
//            return !$this->can($ability, $arguments);
//        }
//
//        // Determine if the entity does not have a given ability.
//        bool cannot(string ability, vector <string> arguments) {
//            return $this->cant($ability, $arguments);
//        }
//};
//
//class authenticatable {
//    protected:
//        string rememberTokenName = "remember_token";
//
//    public:
//        // Get the name of the unique identifier for the user.
//        function getAuthIdentifierName() {
//            return this->getKeyName();
//        }
//
//        // Get the unique identifier for the user.
//        function getAuthIdentifier() {
//            return this->
//            { this->getAuthIdentifierName() };
//        }
//
//        // Get the password for the user.
//        function getAuthPassword() {
//            return this->password;
//        }
//
//        // Get the token value for the "remember me" session.
//        function getRememberToken() {
//            if (!empty(this->getRememberTokenName())) {
//                return this->
//                { this->getRememberTokenName() };
//            }
//        }
//
//        // Set the token value for the "remember me" session.
//        function setRememberToken(value) {
//            if (!empty(this->getRememberTokenName())) {
//                this->
//                { this->getRememberTokenName() } = value;
//            }
//        }
//
//        // Get the column name for the "remember me" token.
//        function getRememberTokenName() {
//            return this->rememberTokenName;
//        }
//};
//
//class authenticatable_user
//        : public model, public authenticatable, public authorizable, public can_reset_password {
//
//};
//
//class two_factor_authenticatable {
//    public:
//        // Get the e-mail address used for two-factor authentication.
//        string getEmailForTwoFactorAuth();
//
//        // Get the country code used for two-factor authentication.
//        string getAuthCountryCode();
//
//        // Get the phone number used for two-factor authentication.
//        string getAuthPhoneNumber();
//
//        // Set the country code and phone number used for two-factor authentication.
//        void setAuthPhoneInformation(int countryCode, int phoneNumber);
//
//        // Get the two-factor provider options in array format.
//        vector <string> getTwoFactorAuthProviderOptions();
//
//        // Set the two-factor provider options in array format.
//        void setTwoFactorAuthProviderOptions(vector <string> options);
//};
//
//trait EntrustUserTrait
//        {
//                //Big block of caching functionality.
//                public function cachedRoles()
//                {
//                    $userPrimaryKey = $this->primaryKey;
//                    $cacheKey = "entrust_roles_for_user_".$this->$userPrimaryKey;
//                    if (Cache::getStore() {
//                        instanceof
//                    }
//                    TaggableStore) {
//                        return Cache::tags(Config::get("entrust.role_user_table"))->remember($cacheKey,
//                                                                                             Config::get("cache.ttl"),
//                                                                                             function()
//                        {
//                            return $this->roles()->get();
//                        });
//                    }
//                    else return $this->roles()->get();
//                }
//                public function save(array $options =[])
//                {   //both inserts and updates
//                    if (Cache::getStore() {
//                        instanceof
//                    }
//                    TaggableStore) {
//                        Cache::tags(Config::get("entrust.role_user_table"))->flush();
//                    }
//                    return parent::save($options);
//                }
//                public function delete(array $options =[])
//                {   //soft or hard
//                    parent::
//                    delete ($options);
//                    if (Cache::getStore() {
//                        instanceof
//                    }
//                    TaggableStore) {
//                        Cache::tags(Config::get("entrust.role_user_table"))->flush();
//                    }
//                }
//                public function restore()
//                {   //soft delete undo"s
//                    parent::restore();
//                    if (Cache::getStore() {
//                        instanceof
//                    }
//                    TaggableStore) {
//                        Cache::tags(Config::get("entrust.role_user_table"))->flush();
//                    }
//                }
//
//                /**
//                 * Many-to-Many relations with Role.
//                 *
//                 * @return \Illuminate\Database\Eloquent\Relations\BelongsToMany
//                 */
//                public function roles()
//                {
//                    return $this->belongsToMany(Config::get("entrust.role"), Config::get("entrust.role_user_table"),
//                                                Config::get("entrust.user_foreign_key"),
//                                                Config::get("entrust.role_foreign_key"));
//                }
//
//                /**
//                 * Boot the user model
//                 * Attach event listener to remove the many-to-many records when trying to delete
//                 * Will NOT delete any records if the user model uses soft deletes.
//                 *
//                 * @return void|bool
//                 */
//                public static function boot()
//                {
//                    parent::boot();
//
//                    static ::deleting (function($user) {
//                        if (!method_exists(Config::get("auth.model"), "bootSoftDeletes")) {
//                            $user->roles()->sync([]);
//                        }
//
//                        return true;
//                    });
//                }
//
//                /**
//                 * Checks if the user has a role by its name.
//                 *
//                 * @param string|array $name       Role name or array of role names.
//                 * @param bool         $requireAll All roles in the array are required.
//                 *
//                 * @return bool
//                 */
//                public function hasRole($name, $requireAll = false)
//                {
//                    if (is_array($name)) {
//                        foreach($name
//                        as
//                        $roleName) {
//                            $hasRole = $this->hasRole($roleName);
//
//                            if ($hasRole && !$requireAll) {
//                                return true;
//                            }
//                            elseif(!$hasRole && $requireAll)
//                            {
//                                return false;
//                            }
//                        }
//
//                        // If we"ve made it this far and $requireAll is FALSE, then NONE of the roles were found
//                        // If we"ve made it this far and $requireAll is TRUE, then ALL of the roles were found.
//                        // Return the value of $requireAll;
//                        return $requireAll;
//                    } else {
//                        foreach($this->cachedRoles()
//                        as
//                        $role) {
//                            if ($role->name == $name) {
//                                return true;
//                            }
//                        }
//                    }
//
//                    return false;
//                }
//
//                /**
//                 * Check if user has a permission by its name.
//                 *
//                 * @param string|array $permission Permission string or array of permissions.
//                 * @param bool         $requireAll All permissions in the array are required.
//                 *
//                 * @return bool
//                 */
//                public function can($permission, $requireAll = false)
//                {
//                    if (is_array($permission)) {
//                        foreach($permission
//                        as
//                        $permName) {
//                            $hasPerm = $this->can($permName);
//
//                            if ($hasPerm && !$requireAll) {
//                                return true;
//                            }
//                            elseif(!$hasPerm && $requireAll)
//                            {
//                                return false;
//                            }
//                        }
//
//                        // If we"ve made it this far and $requireAll is FALSE, then NONE of the perms were found
//                        // If we"ve made it this far and $requireAll is TRUE, then ALL of the perms were found.
//                        // Return the value of $requireAll;
//                        return $requireAll;
//                    } else {
//                        foreach($this->cachedRoles()
//                        as
//                        $role) {
//                            // Validate against the Permission table
//                            foreach($role->cachedPermissions()
//                            as
//                            $perm) {
//                                if (str_is($permission, $perm->name)) {
//                                    return true;
//                                }
//                            }
//                        }
//                    }
//
//                    return false;
//                }
//
//                /**
//                 * Checks role(s) and permission(s).
//                 *
//                 * @param string|array $roles       Array of roles or comma separated string
//                 * @param string|array $permissions Array of permissions or comma separated string.
//                 * @param array        $options     validate_all (true|false) or return_type (boolean|array|both)
//                 *
//                 * @throws \InvalidArgumentException
//                 *
//                 * @return array|bool
//                 */
//                public function ability($roles, $permissions, $options =[])
//                {
//                    // Convert string to array if that"s what is passed in.
//                    if (!is_array($roles)) {
//                        $roles = explode(",", $roles);
//                    }
//                    if (!is_array($permissions)) {
//                        $permissions = explode(",", $permissions);
//                    }
//
//                    // Set up default values and validate options.
//                    if (!isset($options["validate_all"])) {
//                        $options["validate_all"] = false;
//                    } else {
//                        if ($options["validate_all"] != = true && $options["validate_all"] != = false) {
//                            throw new InvalidArgumentException();
//                        }
//                    }
//                    if (!isset($options["return_type"])) {
//                        $options["return_type"] = "boolean";
//                    } else {
//                        if ($options["return_type"] != "boolean" &&
//                            $options["return_type"] != "array" &&
//                            $options["return_type"] != "both") {
//                            throw new InvalidArgumentException();
//                        }
//                    }
//
//                    // Loop through roles and permissions and check each.
//                    $checkedRoles = [];
//                    $checkedPermissions = [];
//                    foreach($roles
//                    as
//                    $role) {
//                        $checkedRoles[$role] = $this->hasRole($role);
//                    }
//                    foreach($permissions
//                    as
//                    $permission) {
//                        $checkedPermissions[$permission] = $this->can($permission);
//                    }
//
//                    // If validate all and there is a false in either
//                    // Check that if validate all, then there should not be any false.
//                    // Check that if not validate all, there must be at least one true.
//                    if (($options["validate_all"] &&
//                         !(in_array(false, $checkedRoles) || in_array(false, $checkedPermissions))) ||
//                        (!$options["validate_all"] &&
//                         (in_array(true, $checkedRoles) || in_array(true, $checkedPermissions)))) {
//                        $validateAll = true;
//                    } else {
//                        $validateAll = false;
//                    }
//
//                    // Return based on option
//                    if ($options["return_type"] == "boolean") {
//                        return $validateAll;
//                    }
//                    elseif($options["return_type"] == "array")
//                    {
//                        return ["roles" => $checkedRoles, "permissions" => $checkedPermissions];
//                    } else {
//                        return [$validateAll, ["roles" => $checkedRoles, "permissions" => $checkedPermissions]];
//                    }
//
//                }
//
//                /**
//                 * Alias to eloquent many-to-many relation"s attach() method.
//                 *
//                 * @param mixed $role
//                 */
//                public function attachRole($role)
//                {
//                    if (is_object($role)) {
//                        $role = $role->getKey();
//                    }
//
//                    if (is_array($role)) {
//                        $role = $role["id"];
//                    }
//
//                    $this->roles()->attach($role);
//                }
//
//                /**
//                 * Alias to eloquent many-to-many relation"s detach() method.
//                 *
//                 * @param mixed $role
//                 */
//                public function detachRole($role)
//                {
//                    if (is_object($role)) {
//                        $role = $role->getKey();
//                    }
//
//                    if (is_array($role)) {
//                        $role = $role["id"];
//                    }
//
//                    $this->roles()->detach($role);
//                }
//
//                /**
//                 * Attach multiple roles to a user
//                 *
//                 * @param mixed $roles
//                 */
//                public function attachRoles($roles)
//                {
//                    foreach($roles
//                    as
//                    $role) {
//                        $this->attachRole($role);
//                    }
//                }
//
//                /**
//                 * Detach multiple roles from a user
//                 *
//                 * @param mixed $roles
//                 */
//                public function detachRoles($roles=null)
//                {
//                    if (!$roles) {
//                        $roles = $this->roles()->get();
//                    }
//
//                    foreach($roles
//                    as
//                    $role) {
//                        $this->detachRole($role);
//                    }
//                }
//
//        }
//
//
//trait CacheFlusherTrait
//        {
//                /**
//                 * Clear permissions cache for specified role.
//                 *
//                 * @param Role $role
//                 */
//                protected function flushRolePermissionsCache(Role $role)
//                {
//                    Cache::forget("entrust_permissions_for_role_{$role->id}");
//                }
//
//                /**
//                 * Clear roles cache for specified user.
//                 *
//                 * @param User $user
//                 */
//                protected function flushUserRolesCache(User $user)
//                {
//                    Cache::forget("entrust_roles_for_user_{$user->id}");
//                }
//        }
//
//class AuthorizationUserTrait
//        : public EntrustUserTrait, public CacheFlusherTrait {
//    public
//
//        function cachedRoles() {
//            return Cache::remember("entrust_roles_for_user_".$this->
//            { $this->primaryKey }, Config::get("cache.ttl"), function()
//            {
//                return $this->roles()->get();
//            });
//        }
//
//    public
//
//        function save(array $options = []) {   //both inserts and updates
//            parent::save($options);
//            $this->flushUserRolesCache($this);
//        }
//
//    public function delete(
//        array $options = []
//        )
//        {   //soft or hard
//            parent::
//            delete ($options);
//            $this->flushUserRolesCache($this);
//        }
//
//    public
//
//        function restore() {   //soft delete undo"s
//            parent::restore();
//            $this->flushUserRolesCache($this);
//        }
//
//};


#endif //WPP_USER_H
