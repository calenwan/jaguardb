/*
 * 
 *
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
 * conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided with the distribution.
 *  Neither the name of the driver nor the names of its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package com.jaguar.jdbc;

import com.jaguar.jdbc.internal.SQLExceptionMapper;
import com.jaguar.jdbc.internal.common.Protocol;
import com.jaguar.jdbc.internal.common.QueryException;
import com.jaguar.jdbc.internal.common.query.JaguarQueryFactory;
import com.jaguar.jdbc.internal.jaguar.JaguarProtocol;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.DriverPropertyInfo;
import java.sql.SQLException;
import java.sql.SQLFeatureNotSupportedException;
import java.util.Properties;
import java.util.logging.Logger;

/**
 * The base SQL JaguarDriver class. User: marcuse Date: Jan 14, 2009 Time: 7:46:09 AM
 */
public final class JaguarDriver implements java.sql.Driver {
    /**
     * the logger.
     */
    private static final Logger log = Logger.getLogger(JaguarDriver.class.getName());
	private int _loginTimeout; // seconds

	public JaguarDriver() {
		_loginTimeout = 5;
	}

    static {
        try {
            DriverManager.registerDriver(new JaguarDriver());
        } catch (SQLException e) {
            throw new RuntimeException("Could not register driver", e);
        }
    }

	public void setLoginTimeout(final int seconds) throws SQLException {
		_loginTimeout = seconds;
	}
	public int getLoginTimeout() throws SQLException {
		return _loginTimeout;
	}

    /**
     * Connect to the given connection string.
     * <p/>
     * the properties are currently ignored
     *
     * @param url  the url to connect to
     * @param info the properties of the connection - ignored at the moment
     * @return a connection
     * @throws SQLException if it is not possible to connect
     */
    public Connection connect(final String url, final Properties info) throws SQLException {
        // TODO: handle the properties!
        // TODO: define what props we support!

        String baseUrl = url;
        int idx = url.lastIndexOf("?");        
        if(idx > 0) {
            baseUrl = url.substring(0,idx);
            String urlParams = url.substring(idx+1);
            setURLParameters(urlParams, info);
        }

        log.finest("Connecting to: " + url);
        try {
            final JDBCUrl jdbcUrl = JDBCUrl.parse(baseUrl);
            if(jdbcUrl == null) {
                return null;
            }
            String userName = info.getProperty("user",jdbcUrl.getUsername());
            String password = info.getProperty("password",jdbcUrl.getPassword());
			String timeout = info.getProperty("timeout", "" );
			Properties newinfo = info;
			if ( timeout.length() < 1 ) {
				newinfo.put("timeout", Integer.toString(this._loginTimeout) );
			}

            final Protocol protocol = new JaguarProtocol(jdbcUrl.getHostname(),
                        jdbcUrl.getPort(),
                        jdbcUrl.getDatabase(),
                        userName,
                        password,
                        newinfo);

            return new JaguarConnection(protocol, new JaguarQueryFactory());
        } catch (QueryException e) {
            throw SQLExceptionMapper.get(e);
        }
    }

    private void setURLParameters(String urlParameters, Properties info) {
        String [] parameters = urlParameters.split("&");
        for(String param : parameters) {
            String [] keyVal = param.split("=");
            info.setProperty(keyVal[0], keyVal[1]);
        }
    }

    /**
     * returns true if the driver can accept the url.
     *
     * @param url the url to test
     * @return true if the url is valid for this driver
     */
    public boolean acceptsURL(final String url) {
        return url.startsWith("jdbc:jaguar://") || url.startsWith("jdbc:jaguar:thin://");
    }

    /**
     * get the property info. TODO: not implemented!
     *
     * @param url  the url to get properties for
     * @param info the info props
     * @return something - not implemented
     * @throws SQLException if there is a problem getting the property info
     */
    public DriverPropertyInfo[] getPropertyInfo(final String url,
                                                final Properties info) throws SQLException 
	{
        return new DriverPropertyInfo[0];
    }

    /**
     * gets the major version of the driver.
     *
     * @return the major versions
     */
    public int getMajorVersion() {
        return 0;
    }

    /**
     * gets the minor version of the driver.
     *
     * @return the minor version
     */
    public int getMinorVersion() {
        return 1;
    }

    /**
     * checks if the driver is jdbc compliant (not yet!).
     *
     * @return false since the driver is not compliant
     */
    public boolean jdbcCompliant() {
        return false;
    }

    /**
     * Retrieves the parent logger for this driver.
     * @return The parent logger
     */
    public Logger getParentLogger() throws SQLFeatureNotSupportedException {
        return log;
    }
}
