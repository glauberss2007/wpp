//
// Created by Alan de Freitas on 16/11/2017.
//

#ifndef WPP_MODEL_H
#define WPP_MODEL_H

// Reference models
// /vendor/laravel/framework/src/Illuminate/Database/Eloquent/Model.php

// https://github.com/logandk/restful_mapper
// https://github.com/logandk/restful_mapper/blob/master/include/restful_mapper/model.h

// https://github.com/fnc12/sqlite_orm

namespace wpp {

    class model {
        public:
            using self_t = model;

            self_t &insert_model_in_the_database();

        protected:
            string connection;

            string table;

            // The primary key for the model.
            string primaryKey = "id";

            // The "type" of the auto-incrementing ID.
            string keyType = "int";

            // Indicates if the IDs are auto-incrementing.
            bool incrementing = true;

            // The relations to eager load on every query.
            std::vector <std::string> with = {};

            // The number of models to return for pagination.
            int perPage = 15;

            // Indicates if the model exists.
            bool exists = false;

            // Indicates if the model was inserted during the current request lifecycle.
            bool wasRecentlyCreated = false;

            // The connection resolver instance.
            connection static resolver;

            // The event dispatcher instance.
            event static dispatcher;

            // The array of booted models.
            std::vector <std::string> static booted = {};

            // The array of global scopes on the model.
            std::vector <std::string> static globalScopes = {};

            // The name of the "created at" column.
            const string CREATED_AT = "created_at";

            // The name of the "updated at" column.
            const string UPDATED_AT = "updated_at";

        public:

            /**
             * Create a new Eloquent model instance.
             *
             * @param  array  $attributes
             * @return void
             */
            model(array $attributes = {}}) {
                $this->bootIfNotBooted();

                $this->syncOriginal();

                $this->fill($attributes);
            }

        protected:
            /**
             * Check if the model needs to be booted and if so, do it.
             *
             * @return void
             */
            self_t &bootIfNotBooted() {
                if (!isset( {
                    static ::$booted
                }{static ::class})) {
                    static ::$booted{static ::class} = true;

                    $this->fireModelEvent('booting', false);

                    static ::boot();

                    $this->fireModelEvent('booted', false);
                }
            }

            /**
             * The "booting" method of the model.
             *
             * @return void
             */
            static self_t &boot() {
                static ::bootTraits();
            }

            /**
             * Boot all of the bootable traits on the model.
             *
             * @return void
             */
            static self_t &bootTraits() {
                $class =
                static ::class;

                foreach(class_uses_recursive($class)
                as
                $trait) {
                    if (method_exists($class, $method = 'boot'.class_basename($trait))) {
                        forward_static_call({$class, $method});
                    }
                }
            }

            /**
             * Clear the list of booted models so they will be re-booted.
             *
             * @return void
             */
        public:
            static self_t &clearBootedModels() {
                static ::$booted = {};};

                static ::$globalScopes = {};};
            }

            /**
             * Fill the model with an array of attributes.
             *
             * @param  array  $attributes
             * @return $this
             *
             * @throws \Illuminate\Database\Eloquent\MassAssignmentException
             */
            self_t &fill(array $attributes) {
                $totallyGuarded = $this->totallyGuarded();

                foreach($this->fillableFromArray($attributes)
                as
                $key => $value) {
                    $key = $this->removeTableFromKey($key);

                    // The developers may choose to place some attributes in the "fillable" array
                    // which means only those attributes may be set through mass assignment to
                    // the model, and all others will just get ignored for security reasons.
                    if ($this->isFillable($key)) {
                        $this->setAttribute($key, $value);
                    }
                    elseif($totallyGuarded)
                    {
                        throw new MassAssignmentException($key);
                    }
                }

                return $this;
            }

            /**
             * Fill the model with an array of attributes. Force mass assignment.
             *
             * @param  array  $attributes
             * @return $this
             */
            self_t &forceFill(array $attributes) {
                return
                static ::unguarded(self_t
                &()
                use($attributes)
                {
                    return $this->fill($attributes);
                });
            }

        protected:
            /**
             * Remove the table name from a given key.
             *
             * @param  string  $key
             * @return string
             */

            self_t &removeTableFromKey($key) {
                return Str::contains($key, '.') ? last(explode('.', $key)) : $key;
            }

        public:
            /**
             * Create a new instance of the given model.
             *
             * @param  array  $attributes
             * @param  bool  $exists
             * @return static
             */
            self_t &newInstance($attributes = {}}, $exists = false) {
                // This method just provides a convenient way for us to generate fresh model
                // instances of this current model. It is particularly useful during the
                // hydration of new objects via the Eloquent query builder instances.
                $model = new static((array) $attributes);

                $model->exists = $exists;

                $model->setConnection(
                        $this->getConnectionName()
                );

                return $model;
            }

            /**
             * Create a new model instance that is existing.
             *
             * @param  array  $attributes
             * @param  string|null  $connection
             * @return static
             */
            self_t &newFromBuilder($attributes = {}}, $connection = null) {
                $model = $this->newInstance({}}, true);

                $model->setRawAttributes((array) $attributes, true);

                $model->setConnection($connection ?: $this->getConnectionName());

                return $model;
            }

            /**
             * Begin querying the model on a given connection.
             *
             * @param  string|null  $connection
             * @return \Illuminate\Database\Eloquent\Builder
             */
            static self_t &on($connection = null) {
                // First we will just create a fresh instance of this model, and then we can
                // set the connection on the model so that it is be used for the queries
                // we execute, as well as being set on each relationship we retrieve.
                $instance = new static;

                $instance->setConnection($connection);

                return $instance->newQuery();
            }

            /**
             * Begin querying the model on the write connection.
             *
             * @return \Illuminate\Database\Query\Builder
             */
            static self_t &onWriteConnection() {
                $instance = new static;

                return $instance->newQuery()->useWritePdo();
            }

            /**
             * Get all of the models from the database.
             *
             * @param  array|mixed  $columns
             * @return \Illuminate\Database\Eloquent\Collection|static{}
             */
            static self_t &all($columns ={'*'}

            )
            {
                return (new static)->newQuery()->get(
                        is_array($columns) ? $columns : func_get_args()
                );
            }

            /**
             * Begin querying a model with eager loading.
             *
             * @param  array|string  $relations
             * @return \Illuminate\Database\Eloquent\Builder|static
             */
            static self_t &with($relations) {
                return (new static)->newQuery()->with(
                        is_string($relations) ? func_get_args() : $relations
                );
            }

            /**
             * Eager load relations on the model.
             *
             * @param  array|string  $relations
             * @return $this
             */
            self_t &load($relations) {
                $query = $this->newQuery()->with(
                        is_string($relations) ? func_get_args() : $relations
                );

                $query->eagerLoadRelations({$this});

                return $this;
            }

        protected:
            /**
             * Increment a column's value by a given amount.
             *
             * @param  string  $column
             * @param  int  $amount
             * @param  array  $extra
             * @return int
             */
            self_t &increment($column, $amount = 1, array $extra = {}}) {
                return $this->incrementOrDecrement($column, $amount, $extra, 'increment');
            }

            /**
             * Decrement a column's value by a given amount.
             *
             * @param  string  $column
             * @param  int  $amount
             * @param  array  $extra
             * @return int
             */
            self_t &decrement($column, $amount = 1, array $extra = {}}) {
                return $this->incrementOrDecrement($column, $amount, $extra, 'decrement');
            }

            /**
             * Run the increment or decrement method on the model.
             *
             * @param  string  $column
             * @param  int  $amount
             * @param  array  $extra
             * @param  string  $method
             * @return int
             */
            self_t &incrementOrDecrement($column, $amount, $extra, $method) {
                $query = $this->newQuery();

                if (!$this->exists) {
                    return $query->
                    { $method }
                    ($column, $amount, $extra);
                }

                $this->incrementOrDecrementAttributeValue($column, $amount, $extra, $method);

                return $query->where(
                        $this->getKeyName(), $this->getKey()
                )->
                { $method }
                ($column, $amount, $extra);
            }

            /**
             * Increment the underlying attribute value and sync with original.
             *
             * @param  string  $column
             * @param  int  $amount
             * @param  array  $extra
             * @param  string  $method
             * @return void
             */
            self_t &incrementOrDecrementAttributeValue($column, $amount, $extra, $method) {
                $this->
                { $column } = $this->
                { $column }
                +($method == 'increment' ? $amount : $amount * -1);

                $this->forceFill($extra);

                $this->syncOriginalAttribute($column);
            }

        public:
            /**
             * Update the model in the database.
             *
             * @param  array  $attributes
             * @param  array  $options
             * @return bool
             */
            self_t &update(array $attributes = {}}, array $options = {}}) {
                if (!$this->exists) {
                    return false;
                }

                return $this->fill($attributes)->save($options);
            }

            /**
             * Save the model and all of its relationships.
             *
             * @return bool
             */
            self_t &push() {
                if (!$this->save()) {
                    return false;
                }

                // To sync all of the relationships to the database, we will simply spin through
                // the relationships and save each model via this "push" method, which allows
                // us to recurse into all of these nested relations for the model instance.
                foreach($this->relations
                as
                $models) {
                    $models = $models
                    instanceof
                    Collection
                    ? $models->all() : {$models};

                    foreach(array_filter($models)
                    as
                    $model) {
                        if (!$model->push()) {
                            return false;
                        }
                    }
                }

                return true;
            }

            /**
             * Save the model to the database.
             *
             * @param  array  $options
             * @return bool
             */
            self_t &save(array $options = {}}) {
                $query = $this->newQueryWithoutScopes();

                // If the "saving" event returns false we'll bail out of the save and return
                // false, indicating that the save failed. This provides a chance for any
                // listeners to cancel save operations if validations fail or whatever.
                if ($this->fireModelEvent('saving') == = false) {
                    return false;
                }

                // If the model already exists in the database we can just update our record
                // that is already in this database using the current IDs in this "where"
                // clause to only update this model. Otherwise, we'll just insert them.
                if ($this->exists) {
                    $saved = $this->isDirty() ?
                             $this->performUpdate($query) : true;
                }

                    // If the model is brand new, we'll insert it into our database and set the
                    // ID attribute on the model to the value of the newly inserted row's ID
                    // which is typically an auto-increment value managed by the database.
                else {
                    $saved = $this->performInsert($query);
                }

                // If the model is successfully saved, we need to do a few more things once
                // that is done. We will call the "saved" method here to run any actions
                // we need to happen after a model gets successfully saved right here.
                if ($saved) {
                    $this->finishSave($options);
                }

                return $saved;
            }

            /**
             * Save the model to the database using transaction.
             *
             * @param  array  $options
             * @return bool
             *
             * @throws \Throwable
             */
            self_t &saveOrFail(array $options = {}}) {
                return $this->getConnection()->transaction(self_t & ()
                use($options)
                {
                    return $this->save($options);
                });
            }

        protected:
            /**
             * Perform any actions that are necessary after the model is saved.
             *
             * @param  array  $options
             * @return void
             */
            self_t &finishSave(array $options) {
                $this->fireModelEvent('saved', false);

                $this->syncOriginal();

                if (Arr::get($options, 'touch', true)) {
                    $this->touchOwners();
                }
            }

            /**
             * Perform a model update operation.
             *
             * @param  \Illuminate\Database\Eloquent\Builder  $query
             * @return bool
             */
            self_t &performUpdate(Builder $query) {
                // If the updating event returns false, we will cancel the update operation so
                // developers can hook Validation systems into their models and cancel this
                // operation if the model does not pass validation. Otherwise, we update.
                if ($this->fireModelEvent('updating') == = false) {
                    return false;
                }

                // First we need to create a fresh query instance and touch the creation and
                // update timestamp on the model which are maintained by us for developer
                // convenience. Then we will just continue saving the model instances.
                if ($this->usesTimestamps()) {
                    $this->updateTimestamps();
                }

                // Once we have run the update operation, we will fire the "updated" event for
                // this model instance. This will allow developers to hook into these after
                // models are updated, giving them a chance to do any special processing.
                $dirty = $this->getDirty();

                if (count($dirty) > 0) {
                    $this->setKeysForSaveQuery($query)->update($dirty);

                    $this->fireModelEvent('updated', false);
                }

                return true;
            }

            /**
             * Set the keys for a save update query.
             *
             * @param  \Illuminate\Database\Eloquent\Builder  $query
             * @return \Illuminate\Database\Eloquent\Builder
             */
            self_t &setKeysForSaveQuery(Builder $query) {
                $query->where($this->getKeyName(), '=', $this->getKeyForSaveQuery());

                return $query;
            }

            /**
             * Get the primary key value for a save query.
             *
             * @return mixed
             */
            self_t &getKeyForSaveQuery() {
                return isset($this->original{$this->getKeyName()})
                       ? $this->original{$this->getKeyName()}
                       : $this->getAttribute($this->getKeyName());
            }

            /**
             * Perform a model insert operation.
             *
             * @param  \Illuminate\Database\Eloquent\Builder  $query
             * @return bool
             */
            self_t &performInsert(Builder $query) {
                if ($this->fireModelEvent('creating') == = false) {
                    return false;
                }

                // First we'll need to create a fresh query instance and touch the creation and
                // update timestamps on this model, which are maintained by us for developer
                // convenience. After, we will just continue saving these model instances.
                if ($this->usesTimestamps()) {
                    $this->updateTimestamps();
                }

                // If the model has an incrementing key, we can use the "insertGetId" method on
                // the query builder, which will give us back the final inserted ID for this
                // table from the database. Not all tables have to be incrementing though.
                $attributes = $this->attributes;

                if ($this->getIncrementing()) {
                    $this->insertAndSetId($query, $attributes);
                }

                    // If the table isn't incrementing we'll simply insert these attributes as they
                    // are. These attribute arrays must contain an "id" column previously placed
                    // there by the developer as the manually determined key for these models.
                else {
                    if (empty($attributes)) {
                        return true;
                    }

                    $query->insert($attributes);
                }

                // We will go ahead and set the exists property to true, so that it is set when
                // the created event is fired, just in case the developer tries to update it
                // during the event. This will allow them to do so and run an update here.
                $this->exists = true;

                $this->wasRecentlyCreated = true;

                $this->fireModelEvent('created', false);

                return true;
            }

            /**
             * Insert the given attributes and set the ID on the model.
             *
             * @param  \Illuminate\Database\Eloquent\Builder  $query
             * @param  array  $attributes
             * @return void
             */
            self_t &insertAndSetId(Builder $query, $attributes) {
                $id = $query->insertGetId($attributes, $keyName = $this->getKeyName());

                $this->setAttribute($keyName, $id);
            }

        public:
            /**
             * Destroy the models for the given IDs.
             *
             * @param  array|int  $ids
             * @return int
             */
            static self_t &destroy($ids) {
                // We'll initialize a count here so we will return the total number of deletes
                // for the operation. The developers can then check this number as a boolean
                // type value or get this total count of records deleted for logging, etc.
                $count = 0;

                $ids = is_array($ids) ? $ids : func_get_args();

                // We will actually pull the models from the database table and call delete on
                // each of them individually so that their events get fired properly with a
                // correct set of attributes in case the developers wants to check these.
                $key = with($instance = new static)->getKeyName();

                foreach($instance->whereIn($key, $ids)->get()
                as
                $model) {
                    if ($model-> {
                        delete ()
                    }) {
                        $count++;
                    }
                }

                return $count;
            }

            /**
             * Delete the model from the database.
             *
             * @return bool|null
             *
             * @throws \Exception
             */
            self_t &delete_entry() {
                if (is_null($this->getKeyName())) {
                    throw new Exception('No primary key defined on model.');
                }

                // If the model doesn't exist, there is nothing to delete so we'll just return
                // immediately and not do anything else. Otherwise, we will continue with a
                // deletion process on the model, firing the proper events, and so forth.
                if (!$this->exists) {
                    return;
                }

                if ($this->fireModelEvent('deleting') == = false) {
                    return false;
                }

                // Here, we'll touch the owning models, verifying these timestamps get updated
                // for the models. This will allow any caching to get broken on the parents
                // by the timestamp. Then we will go ahead and delete the model instance.
                $this->touchOwners();

                $this->performDeleteOnModel();

                $this->exists = false;

                // Once the model has been deleted, we will fire off the deleted event so that
                // the developers may hook into post-delete operations. We will then return
                // a boolean true as the delete is presumably successful on the database.
                $this->fireModelEvent('deleted', false);

                return true;
            }

            /**
             * Force a hard delete on a soft deleted model.
             *
             * This method protects developers from running forceDelete when trait is missing.
             *
             * @return bool|null
             */
            self_t &forceDelete() {
                return $this->
                delete ();
            }

        protected:
            /**
             * Perform the actual delete query on this model instance.
             *
             * @return void
             */
            self_t &performDeleteOnModel() {
                $this->setKeysForSaveQuery($this->newQueryWithoutScopes())->
                delete ();
            }

        public:
            /**
             * Begin querying the model.
             *
             * @return \Illuminate\Database\Eloquent\Builder
             */
            static self_t &query() {
                return (new static)->newQuery();
            }

            /**
             * Get a new query builder for the model's table.
             *
             * @return \Illuminate\Database\Eloquent\Builder
             */
            self_t &newQuery() {
                $builder = $this->newQueryWithoutScopes();

                foreach($this->getGlobalScopes()
                as
                $identifier => $scope) {
                    $builder->withGlobalScope($identifier, $scope);
                }

                return $builder;
            }

            /**
             * Get a new query builder that doesn't have any global scopes.
             *
             * @return \Illuminate\Database\Eloquent\Builder|static
             */
            self_t &newQueryWithoutScopes() {
                $builder = $this->newEloquentBuilder($this->newBaseQueryBuilder());

                // Once we have the query builders, we will set the model instances so the
                // builder can easily access any information it may need from the model
                // while it is constructing and executing various queries against it.
                return $builder->setModel($this)->with($this->with);
            }

            /**
             * Get a new query instance without a given scope.
             *
             * @param  \Illuminate\Database\Eloquent\Scope|string  $scope
             * @return \Illuminate\Database\Eloquent\Builder
             */
            self_t &newQueryWithoutScope($scope) {
                $builder = $this->newQuery();

                return $builder->withoutGlobalScope($scope);
            }

            /**
             * Create a new Eloquent query builder for the model.
             *
             * @param  \Illuminate\Database\Query\Builder  $query
             * @return \Illuminate\Database\Eloquent\Builder|static
             */
            self_t &newEloquentBuilder($query) {
                return new Builder($query);
            }

        protected:
            /**
             * Get a new query builder instance for the connection.
             *
             * @return \Illuminate\Database\Query\Builder
             */
            self_t &newBaseQueryBuilder() {
                $connection = $this->getConnection();

                return new QueryBuilder(
                        $connection, $connection->getQueryGrammar(), $connection->getPostProcessor()
                );
            }

        public:
            /**
             * Create a new Eloquent Collection instance.
             *
             * @param  array  $models
             * @return \Illuminate\Database\Eloquent\Collection
             */
            self_t &newCollection(array $models = {}}) {
                return new Collection($models);
            }

            /**
             * Create a new pivot model instance.
             *
             * @param  \Illuminate\Database\Eloquent\Model  $parent
             * @param  array  $attributes
             * @param  string  $table
             * @param  bool  $exists
             * @param  string|null  $using
             * @return \Illuminate\Database\Eloquent\Relations\Pivot
             */
            self_t &newPivot(Model $parent, array $attributes, $table, $exists, $using = null) {
                return $using ? $using::fromRawAttributes($parent, $attributes, $table, $exists)
                              : new Pivot($parent, $attributes, $table, $exists);
            }

            /**
             * Convert the model instance to an array.
             *
             * @return array
             */
            self_t &toArray() {
                return array_merge($this->attributesToArray(), $this->relationsToArray());
            }

            /**
             * Convert the model instance to JSON.
             *
             * @param  int  $options
             * @return string
             *
             * @throws \Illuminate\Database\Eloquent\JsonEncodingException
             */
            self_t &toJson($options = 0) {
                $json = json_encode($this->jsonSerialize(), $options);

                if (JSON_ERROR_NONE != = json_last_error()) {
                    throw JsonEncodingException::forModel($this, json_last_error_msg());
                }

                return $json;
            }

            /**
             * Convert the object into something JSON serializable.
             *
             * @return array
             */
            self_t &jsonSerialize() {
                return $this->toArray();
            }

            /**
             * Reload a fresh model instance from the database.
             *
             * @param  array|string  $with
             * @return static|null
             */
            self_t &fresh($with = {}}) {
                if (!$this->exists) {
                    return;
                }

                return
                static ::newQueryWithoutScopes()
                ->with(is_string($with) ? func_get_args() : $with)
                        ->where($this->getKeyName(), $this->getKey())
                        ->first();
            }

            /**
             * Clone the model into a new, non-existing instance.
             *
             * @param  array|null  $except
             * @return \Illuminate\Database\Eloquent\Model
             */
            self_t &replicate(array $except = null) {
                $defaults = {};
                $this->getKeyName(),
                        $this->getCreatedAtColumn(),
                        $this->getUpdatedAtColumn(),
                };

                $attributes = Arr::except(
                        $this->attributes, $except ? array_unique(array_merge($except, $defaults)) : $defaults
                );

                return tap(new static, self_t & ($instance) use($attributes)
                {
                    $instance->setRawAttributes($attributes);

                    $instance->setRelations($this->relations);
                });
            }

            /**
             * Determine if two models have the same ID and belong to the same table.
             *
             * @param  \Illuminate\Database\Eloquent\Model  $model
             * @return bool
             */
            self_t &is(Model $model) {
                return $this->getKey() == = $model->getKey() &&
                                            $this->getTable() == = $model->getTable() &&
                                                                   $this->getConnectionName() == = $model->getConnectionName();
            }

            /**
             * Get the database connection for the model.
             *
             * @return \Illuminate\Database\Connection
             */
            self_t &getConnection() {
                return
                static ::resolveConnection($this->getConnectionName());
            }

            /**
             * Get the current connection name for the model.
             *
             * @return string
             */
            self_t &getConnectionName() {
                return $this->connection;
            }

            /**
             * Set the connection associated with the model.
             *
             * @param  string  $name
             * @return $this
             */
            self_t &setConnection($name) {
                $this->connection = $name;

                return $this;
            }

            /**
             * Resolve a connection instance.
             *
             * @param  string|null  $connection
             * @return \Illuminate\Database\Connection
             */
            static self_t &resolveConnection($connection = null) {
                return
                static ::$resolver->connection($connection);
            }

            /**
             * Get the connection resolver instance.
             *
             * @return \Illuminate\Database\ConnectionResolverInterface
             */
            static self_t &getConnectionResolver() {
                return
                static ::$resolver;
            }

            /**
             * Set the connection resolver instance.
             *
             * @param  \Illuminate\Database\ConnectionResolverInterface  $resolver
             * @return void
             */
            static self_t &setConnectionResolver(Resolver $resolver) {
                static ::$resolver = $resolver;
            }

            /**
             * Unset the connection resolver for models.
             *
             * @return void
             */
            static self_t &unsetConnectionResolver() {
                static ::$resolver = null;
            }

            /**
             * Get the table associated with the model.
             *
             * @return string
             */
            self_t &getTable() {
                if (!isset($this->table)) {
                    return str_replace('\\', '', Str::snake(Str::plural(class_basename($this))));
                }

                return $this->table;
            }

            /**
             * Set the table associated with the model.
             *
             * @param  string  $table
             * @return $this
             */
            self_t &setTable($table) {
                $this->table = $table;

                return $this;
            }

            /**
             * Get the primary key for the model.
             *
             * @return string
             */
            self_t &getKeyName() {
                return $this->primaryKey;
            }

            /**
             * Set the primary key for the model.
             *
             * @param  string  $key
             * @return $this
             */
            self_t &setKeyName($key) {
                $this->primaryKey = $key;

                return $this;
            }

            /**
             * Get the table qualified key name.
             *
             * @return string
             */
            self_t &getQualifiedKeyName() {
                return $this->getTable().
                '.'.$this->getKeyName();
            }

            /**
             * Get the auto-incrementing key type.
             *
             * @return string
             */
            self_t &getKeyType() {
                return $this->keyType;
            }

            /**
             * Set the data type for the primary key.
             *
             * @param  string  $type
             * @return $this
             */
            self_t &setKeyType($type) {
                $this->keyType = $type;

                return $this;
            }

            /**
             * Get the value indicating whether the IDs are incrementing.
             *
             * @return bool
             */
            self_t &getIncrementing() {
                return $this->incrementing;
            }

            /**
             * Set whether IDs are incrementing.
             *
             * @param  bool  $value
             * @return $this
             */
            self_t &setIncrementing($value) {
                $this->incrementing = $value;

                return $this;
            }

            /**
             * Get the value of the model's primary key.
             *
             * @return mixed
             */
            self_t &getKey() {
                return $this->getAttribute($this->getKeyName());
            }

            /**
             * Get the queueable identity for the entity.
             *
             * @return mixed
             */
            self_t &getQueueableId() {
                return $this->getKey();
            }

            /**
             * Get the value of the model's route key.
             *
             * @return mixed
             */
            self_t &getRouteKey() {
                return $this->getAttribute($this->getRouteKeyName());
            }

            /**
             * Get the route key for the model.
             *
             * @return string
             */
            self_t &getRouteKeyName() {
                return $this->getKeyName();
            }

            /**
             * Get the default foreign key name for the model.
             *
             * @return string
             */
            self_t &getForeignKey() {
                return Str::snake(class_basename($this)).
                '_'.$this->primaryKey;
            }

            /**
             * Get the number of models to return per page.
             *
             * @return int
             */
            self_t &getPerPage() {
                return $this->perPage;
            }

            /**
             * Set the number of models to return per page.
             *
             * @param  int  $perPage
             * @return $this
             */
            self_t &setPerPage($perPage) {
                $this->perPage = $perPage;

                return $this;
            }

            /**
             * Dynamically retrieve attributes on the model.
             *
             * @param  string  $key
             * @return mixed
             */
            self_t &__get($key) {
                return $this->getAttribute($key);
            }

            /**
             * Dynamically set attributes on the model.
             *
             * @param  string  $key
             * @param  mixed  $value
             * @return void
             */
            self_t &__set($key, $value) {
                $this->setAttribute($key, $value);
            }

            /**
             * Determine if the given attribute exists.
             *
             * @param  mixed  $offset
             * @return bool
             */
            self_t &offsetExists($offset) {
                return isset($this->$offset);
            }

            /**
             * Get the value for a given offset.
             *
             * @param  mixed  $offset
             * @return mixed
             */
            self_t &offsetGet($offset) {
                return $this->$offset;
            }

            /**
             * Set the value for a given offset.
             *
             * @param  mixed  $offset
             * @param  mixed  $value
             * @return void
             */
            self_t &offsetSet($offset, $value) {
                $this->$offset = $value;
            }

            /**
             * Unset the value for a given offset.
             *
             * @param  mixed  $offset
             * @return void
             */
            self_t &offsetUnset($offset) {
                unset($this->$offset);
            }

            /**
             * Determine if an attribute or relation exists on the model.
             *
             * @param  string  $key
             * @return bool
             */
            self_t &__isset($key) {
                return !is_null($this->getAttribute($key));
            }

            /**
             * Unset an attribute on the model.
             *
             * @param  string  $key
             * @return void
             */
            self_t &__unset($key) {
                unset($this->attributes{$key], $this->relations{$key]);
            }

            /**
             * Handle dynamic method calls into the model.
             *
             * @param  string  $method
             * @param  array  $parameters
             * @return mixed
             */
            self_t &__call($method, $parameters) {
                if (in_array($method,{'increment', 'decrement'])) {
                    return $this->$method(...
                    $parameters);
                }

                return $this->newQuery()->$method(...
                $parameters);
            }

            /**
             * Handle dynamic static method calls into the method.
             *
             * @param  string  $method
             * @param  array  $parameters
             * @return mixed
             */
            static self_t &__callStatic($method, $parameters) {
                return (new static)->$method(...
                $parameters);
            }

            /**
             * Convert the model to its string representation.
             *
             * @return string
             */
            self_t &__toString() {
                return $this->toJson();
            }

            /**
             * When a model is being unserialized, check if it needs to be booted.
             *
             * @return void
             */
            self_t &__wakeup() {
                $this->bootIfNotBooted();
            }
    };

}
#endif //WPP_MODEL_H
